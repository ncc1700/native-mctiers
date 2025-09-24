
#include <Windows.h>
#include <wchar.h>



LRESULT WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
    switch (uMsg) {
        case WM_PAINT:
            PAINTSTRUCT s;
            BeginPaint(hWnd, &s);
            HDC dc = GetDC(hWnd);
            HBRUSH b = CreateSolidBrush(RGB(255, 90, 0));
            SelectObject(dc, b);
            Rectangle(dc, 50, 50, 100, 100);
            DeleteDC(dc);
            DeleteObject(b);
            wprintf(L"h");
            EndPaint(hWnd, &s);
            break;
        case WM_CLOSE:
            CloseWindow(hWnd);
            ExitProcess(0);
            break;
    }
    return DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

#ifndef DEBUG
INT wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd)
#else 
INT wmain(INT argc, PWCHAR argv[])
#endif
{
    HICON icon = LoadIconW(hInstance, L"DEFAULTICON");
    MSG msg;
    WNDCLASSW wc;
    wc.lpszClassName = L"Native-MCTiers";
    wc.lpfnWndProc = WndProc;
    wc.hIcon = icon;
    
    RegisterClassW(&wc);
    HWND hwnd = CreateWindowExW(0, L"Native-MCTiers", 
        L"Native MCTiers", 
        WS_TILEDWINDOW | WS_VISIBLE, 
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, hInstance, NULL);
    ShowWindow(hwnd, SW_SHOW);
    while(GetMessageW(&msg, hwnd, 0, 0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    CloseWindow(hwnd);
    return 0;
}