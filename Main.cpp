#include "Application.h"
#include <ctime>

float seconds_now() {
	static LARGE_INTEGER s_frequency;
	static BOOL s_use_qpc = QueryPerformanceFrequency(&s_frequency);
	if (s_use_qpc) {
		LARGE_INTEGER now;
		QueryPerformanceCounter(&now);
		return(now.QuadPart) / s_frequency.QuadPart;
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

	float DesiredFPS = 60.0f;

	Application * theApp = new Application();

	if (FAILED(theApp->Initialise(hInstance, nCmdShow)))
	{
		return -1;
	}

    // Main message loop
    MSG msg = {0};

	float deltaTime = 0.0f;

    while (WM_QUIT != msg.message)
    {
		// Update start time
		float startTime = seconds_now();
		//clock_t startTime = clock();

        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
        }
        else
        {
			theApp->Update(0.01667f);
            theApp->Draw();

			//Calculate Delta Time in milliseconds
			float endTime = seconds_now();
			//clock_t endTime = clock();
			deltaTime = (endTime - startTime);

			if (deltaTime < (1.0f / DesiredFPS))
			{
				Sleep(((1.0f / DesiredFPS) - deltaTime) * 1000.0f);
			}

			/*
			if (deltaTime * (DesiredFPS/1000.0f) < 1)
			{
				Sleep(((1 / DesiredFPS) - deltaTime));
			}*/
        }
    }

	delete theApp;
	theApp = nullptr;

    return (int) msg.wParam;
}

