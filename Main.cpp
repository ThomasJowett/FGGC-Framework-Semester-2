#include "Application.h"
#include <ctime>
#include <chrono>

long long Milliseconds_now() {
	static LARGE_INTEGER s_frequency;
	static BOOL s_use_qpc = QueryPerformanceFrequency(&s_frequency);
	if (s_use_qpc) {
		LARGE_INTEGER now;
		QueryPerformanceCounter(&now);
		return((now.QuadPart * 1000) / s_frequency.QuadPart);
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
		auto start = std::chrono::high_resolution_clock::now();
		// Update start time
		long long startTime = Milliseconds_now();
		//clock_t startTime = clock();

        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
        }
        else
        {
			if (deltaTime < (1.0f / DesiredFPS))
			{
				theApp->Update(1.0f / DesiredFPS);
			}
			else
			{
				theApp->Update(deltaTime);
			}
			//theApp->Update(deltaTime);
            theApp->Draw();

			//Calculate Delta Time in milliseconds
			auto end = std::chrono::high_resolution_clock::now();
			long long endTime = Milliseconds_now();
			//clock_t endTime = clock();
			deltaTime = (endTime - startTime)/1000.0f;
			std::chrono::duration<double> elasped = end - start;
			//deltaTime = elasped.count();

			if (deltaTime < (1.0f / DesiredFPS))
			{
				Sleep(((1.0f / DesiredFPS) - deltaTime) * 1000.0f);
			}
        }
    }

	delete theApp;
	theApp = nullptr;

    return (int) msg.wParam;
}

