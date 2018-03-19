#include "Application.h"
#include <ctime>

float milliseconds_now() {
	static LARGE_INTEGER s_frequency;
	static BOOL s_use_qpc = QueryPerformanceFrequency(&s_frequency);
	if (s_use_qpc) {
		LARGE_INTEGER now;
		QueryPerformanceCounter(&now);
		return(1000.0f * now.QuadPart) / s_frequency.QuadPart;
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

	float DesiredFPS = 10;

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
		float startTime = milliseconds_now();
		//clock_t startTime = clock();

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
			float endTime = milliseconds_now();
			//clock_t endTime = clock();
			deltaTime = (endTime - startTime);
			
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

