
#include "guiabs/buttons.h"
#include "guiabs/inputbox.h"
#include "guiabs/states.h"
#include "guiabs/text.h"
#include "typedef.h"
#include <Windows.h>


HWND h;


LRESULT WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
    switch (uMsg) {
        case WM_CREATE:
            break;
        case WM_PAINT:
            RepaintWindow(hWnd);
            InitializeAllButtons(hWnd);
            InitializeAllInputBoxs(hWnd);
            InitializeAllTexts(hWnd);
            InitializeAllInputBoxsBackground(hWnd);
            break;
        case WM_COMMAND:
            CheckForAllButtonInteractionState(wParam);
            break;
        case WM_CLOSE:
            CloseWindow(hWnd);
            EndGui();
            ExitProcess(0);
            break;
    }
    return DefWindowProcW(hWnd, uMsg, wParam, lParam);
}


VOID ButtonCallback(LPVOID arg){
    WCHAR text[16];
    GetTextFromInputBox(text, 0);
    MessageBoxW(NULL, text, L"h", MB_OK | MB_ICONERROR);
}


INT wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd){   
    SetupGui();
    CreateInputBox(L"", Width() / 2 - 70, Height() / 2 - 100, 130, 21);
    CreateText(L"Search", Width() / 2 - 30, Height() / 2 - 130, 0, 0);
    CreateButton(L"Search (MCTiers)", (Width() / 2 - 75) , Height() / 2 - 60, 140, 30, ButtonCallback);
    CreateButton(L"Search (PVPTiers)", (Width() / 2 - 80) , Height() / 2 - 25, 150, 30, ButtonCallback);
    CreateButton(L"Search (Subtiers)", (Width() / 2 - 75) , Height() / 2 + 10, 140, 30, ButtonCallback);
    
    HICON icon = LoadIconW(hInstance, L"DEFAULTICON");
    MSG msg;
    WNDCLASSEXW wc = {0};
    wc.cbSize = sizeof(WNDCLASSEXW);
    wc.lpszClassName = L"Native-MCTiers";
    wc.lpfnWndProc = WndProc;
    wc.hIcon = icon;
    wc.hInstance = hInstance;
    
    RegisterClassExW(&wc);

    HWND hwnd = CreateWindowExW(0, L"Native-MCTiers", 
        L"Native MCTiers", 
        WS_OVERLAPPEDWINDOW & ~(WS_THICKFRAME | WS_MAXIMIZEBOX), 
        CW_USEDEFAULT, CW_USEDEFAULT, Width(), Height(), NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, SW_SHOW);
    while(GetMessageW(&msg, hwnd, 0, 0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    CloseWindow(hwnd);
    EndGui();
    return 0;
}