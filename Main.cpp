#include "Application.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

	Application * theApp = new Application();

	if (FAILED(theApp->Initialise(hInstance, nCmdShow)))
	{
		return -1;
	}

    // Main message loop
    MSG msg = {0};

    while (WM_QUIT != msg.message)
    {
		// Update our time
		static float timeSinceStart = 0.0f;
		float oldTime = 0.0f;
		static DWORD dwTimeStart = 0;

		DWORD dwTimeCur = GetTickCount();

		if (dwTimeStart == 0)
			dwTimeStart = dwTimeCur;

		timeSinceStart = (dwTimeCur - dwTimeStart) / 1000.0f;

		//Calculate Delta Time
		float deltaTime = timeSinceStart - oldTime;


        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
        }
        else
        {
			theApp->Update(deltaTime);
            theApp->Draw();
        }
    }

	delete theApp;
	theApp = nullptr;

    return (int) msg.wParam;
}