#include "Application.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

	float DesiredFPS = 60;

	Application * theApp = new Application();

	if (FAILED(theApp->Initialise(hInstance, nCmdShow)))
	{
		return -1;
	}

    // Main message loop
    MSG msg = {0};

	float deltaTime = 1.0f;

    while (WM_QUIT != msg.message)
    {
		// Update our time
		float startTime = (float)timeGetTime();

        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
        }
        else
        {
			theApp->Update(deltaTime);
            theApp->Draw();

			//Calculate Delta Time in milliseconds
			deltaTime = ((float)timeGetTime() - startTime);

			if (deltaTime * (DesiredFPS * 0.001f) < 1)
			{
				Sleep(((1 / DesiredFPS) * 1000 - deltaTime));
			}

			if (deltaTime > 1)
			{
				MessageBox(nullptr, L"to_string(deltaTime)", L"Error", MB_OK);
			}
        }
    }

	delete theApp;
	theApp = nullptr;

    return (int) msg.wParam;
}