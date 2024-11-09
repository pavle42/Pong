#include <windows.h>

bool running = true;

LRESULT CALLBACK window_callback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;

    switch (uMsg)
    {
        case WM_CLOSE:
        case WM_DESTROY:
            running = false;
            break;
        default:
            result = DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return result;
}

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	//Creating the window class
	WNDCLASS window_class = {};
	window_class.style = CS_HREDRAW | CS_VREDRAW;
	window_class.lpszClassName = TEXT("Game Window Class");
	window_class.lpfnWndProc = window_callback;

	//Register class
	RegisterClass(&window_class);

	//Create window
    HWND window = CreateWindow(
        window_class.lpszClassName,    // Window class name
        TEXT("Pong"),   // Window title
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,          // Window style
        CW_USEDEFAULT,                  // Initial X position
        CW_USEDEFAULT,                  // Initial Y position
        1280,             // Width of the window
        720,            // Height of the window
        0,        // Parent window (if any)
        0,            // Menu handle or control ID
        hInstance,    // Application instance handle
        0          // Additional application data
    );

    //Update
    while (running)
    {
        //Input
        MSG message;
        while (PeekMessage(&message, window, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
    }
}