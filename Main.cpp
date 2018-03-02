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

	float deltaTime = 0.0f;
	LARGE_INTEGER clockFrequency;

    while (WM_QUIT != msg.message)
    {
		QueryPerformanceFrequency(&clockFrequency);

		// Update our time
		LARGE_INTEGER startTime;
		LARGE_INTEGER endTime;
		QueryPerformanceCounter(&startTime);

        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
        }
        else
        {
			theApp->Update(deltaTime);
            theApp->Draw();
			
			QueryPerformanceCounter(&endTime);
			LARGE_INTEGER delta;
			delta.QuadPart = (endTime.QuadPart - startTime.QuadPart);

			//Calculate Delta Time in milliseconds
			deltaTime = (((float)delta.QuadPart) / clockFrequency.QuadPart)*1000;

			if (deltaTime * (DesiredFPS * 0.001f) < 1)
			{
				Sleep(((1 / DesiredFPS) * 1000 - deltaTime));
			}
        }
    }

	delete theApp;
	theApp = nullptr;

    return (int) msg.wParam;
}