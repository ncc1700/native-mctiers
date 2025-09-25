#include "states.h"





static UINT64 key = 0;
static HFONT font = NULL;

static UINT64 width = 800;
static UINT64 height = 600;

UINT64 GetKey(){
    key++;
    return key - 1;
}

static inline HFONT CreateFontForSystem(WCHAR* font, int fontsize) {
    return CreateFontW(
        -MulDiv(fontsize, GetDeviceCaps(GetDC(NULL), LOGPIXELSY), 72),
        0,
        0,
        0,
        FW_NORMAL,
        FALSE,
        FALSE,
        FALSE,
        DEFAULT_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_DONTCARE,
        font
    );
}

HFONT GetFont(){
    return font;
}

VOID SetupGui(){
    UINT64 sWidth = GetSystemMetrics(SM_CXSCREEN);
    UINT64 sHeight = GetSystemMetrics(SM_CYSCREEN);
    width = sWidth / 4;
    height = sHeight / 2;
    font = CreateFontForSystem(L"Arial", 12);
}

VOID EndGui(){
    CloseHandle(font);
}

UINT64 Width(){
    return width;
}

UINT64 Height(){
    return height;
}

VOID SetWidth(UINT64 newWidth){
    width = newWidth;
}

VOID SetHeight(UINT64 newHeight){
    height = newHeight;
}

VOID RepaintWindow(HWND hWnd){
    HDC dc = GetDC(hWnd);
    HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));
    RECT r = {0, 0, Width(), Height()};
    FillRect(dc, &r, brush);
    DeleteDC(dc);
    DeleteObject(brush);
}