#include "Application.h"

long long milliseconds_now() {
	static LARGE_INTEGER s_frequency;
	static BOOL s_use_qpc = QueryPerformanceFrequency(&s_frequency);
	if (s_use_qpc) {
		LARGE_INTEGER now;
		QueryPerformanceCounter(&now);
		return(1000LL * now.QuadPart) / s_frequency.QuadPart;
	}
	else
	{
		return GetTickCount();
	}
}

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
	//LARGE_INTEGER clockFrequency;
	//QueryPerformanceFrequency(&clockFrequency);

    while (WM_QUIT != msg.message)
    {
		

		// Update start time
		long long startTime = milliseconds_now();

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
			long long endTime = milliseconds_now();
			deltaTime = (float)(endTime-startTime);
			
			if (deltaTime * (DesiredFPS/1000.0f) < 1)
			{
				Sleep(((1 / DesiredFPS) - deltaTime/1000.0f));
			}
        }
    }

	delete theApp;
	theApp = nullptr;

    return (int) msg.wParam;
}

