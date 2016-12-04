#include <stdio.h>
#include <windows.h>

static BOOL IsRunning = TRUE;

static double GTimePassed = 0;
static double SecondsPerTick = 0;
static __int64 GTimeCount = 0;

float Sys_InitFloatTime(void)
{
    LARGE_INTEGER Frequency;
    QueryPerformanceFrequency(&Frequency);

    SecondsPerTick = 1.0 / (double)Frequency.QuadPart;

    LARGE_INTEGER Counter;
    QueryPerformanceCounter(&Counter);

    GTimeCount = Counter.QuadPart;

    return 0;
}

float Sys_FloatTime(void)
{
    LARGE_INTEGER Counter;
    QueryPerformanceCounter(&Counter);

    __int64 Interval = Counter.QuadPart - GTimeCount;
    GTimeCount = Counter.QuadPart;
    double SecondsGoneBy = (double)Interval * SecondsPerTick;
    GTimePassed += SecondsGoneBy;

    return (float)GTimePassed;
}

void Sys_Shutdown(void)
{
    IsRunning = FALSE;
}

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT Result = 0;

	switch (uMsg)
	{
		case WM_ACTIVATE:
            break;
		case WM_CREATE:
            break;
		case WM_DESTROY:
            Sys_Shutdown();
			break;
		default:
			Result = DefWindowProc(hwnd, uMsg, wParam, lParam);
			break;
	}

	return Result;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wc = { 0 };
	wc.lpfnWndProc = MainWndProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName = "Module 2";

	if (!RegisterClass(&wc))
	{
		exit(EXIT_FAILURE);
	}

	HWND mainWindow;
	DWORD WindowStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE;

	RECT r;
	r.top = r.left = 0;
	r.right = 800;
	r.bottom = 600;

	AdjustWindowRect(&r, WindowStyle, FALSE);

	mainWindow = CreateWindowEx(
		0,
		"Module 2",
		"Lesson 2.4",
		WindowStyle,
        CW_USEDEFAULT,
		CW_USEDEFAULT,
		r.right - r.left,
		r.bottom - r.top,
		NULL,
		NULL,
		hInstance,
		0
	);

	ShowWindow(mainWindow, SW_SHOWDEFAULT);

	HDC DeviceContext = GetDC(mainWindow);
	PatBlt(DeviceContext, 0, 0, 800, 600, BLACKNESS);
	ReleaseDC(mainWindow, DeviceContext);
    
    float timecount = Sys_InitFloatTime();

	MSG msg;
	LRESULT Result;
	while (IsRunning)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			Result = DispatchMessage(&msg);
		};

        float newtime = Sys_FloatTime();

        char buf[64];
        sprintf_s(buf, 64, "Total time: %3.7f \n", newtime);
        OutputDebugString(buf);

        Sleep(1);
	}

	return 0;
}
