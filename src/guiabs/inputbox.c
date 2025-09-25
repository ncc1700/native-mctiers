#include "inputbox.h"
#include "states.h"
#include <wchar.h>




typedef struct _INPUT_BOX_NODE {
    HWND hWnd;
    UINT64 key;
    WCHAR text[40];
    UINT16 x;
    UINT16 y;
    UINT16 width;
    UINT16 height;
    struct _INPUT_BOX_NODE* next;
    struct _INPUT_BOX_NODE* prev;
} INPUT_BOX_NODE;

static INPUT_BOX_NODE* first = NULL;
static INPUT_BOX_NODE* initial = NULL;

static inline VOID CreateInputBoxNode(UINT16 key, WCHAR* text, UINT16 x, UINT16 y, UINT16 width, UINT16 height){
    if(initial == NULL){
        initial = (INPUT_BOX_NODE*)VirtualAlloc(NULL, sizeof(INPUT_BOX_NODE), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
        initial->prev = NULL;
        initial->next = NULL;
        first = initial;
    } else {
        initial->next = (INPUT_BOX_NODE*)VirtualAlloc(NULL, sizeof(INPUT_BOX_NODE), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
        initial->next->prev = initial;
        initial->next->next = NULL;
        initial = initial->next;
    }
    swprintf_s(initial->text, 40, L"%s", text);
    initial->x = x;
    initial->y = y;
    initial->width = width;
    initial->height = height;
    initial->key = key;
}


HWND GetInputBoxHWNDThroughKey(UINT16 key){
    INPUT_BOX_NODE* prev = initial;
    initial = first;
    HWND result = NULL;
    while(initial != NULL){
        if(initial->key == key){
            result = initial->hWnd;
            break;
        }
        initial = initial->next;
    }
    initial = prev;
    return result;
}



VOID CreateInputBox(LPWSTR text, INT x, INT y, INT width, INT height){
    CreateInputBoxNode(GetKey(), text, x, y, width, height);
}



VOID InitializeAllInputBoxs(HWND winHWND){
    INPUT_BOX_NODE* prev = initial;
    initial = first;
    HWND result = NULL;
    while(initial != NULL){
        if(initial->hWnd != NULL){
            initial = initial->next;
            continue;
        } 
        initial->hWnd = CreateWindowW(
            L"EDIT",
            initial->text,
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL,
            initial->x, initial->y, initial->width, initial->height, winHWND, 
            (HMENU)initial->key, (HINSTANCE)GetWindowLongPtr(winHWND, GWLP_HINSTANCE), NULL
        );
        SendMessage(initial->hWnd, WM_SETFONT, (WPARAM)GetFont(), TRUE);
        initial = initial->next;
    }
    initial = prev;
}

VOID InitializeAllInputBoxsBackground(HWND winHWND){
    INPUT_BOX_NODE* prev = initial;
    HDC dc = GetDC(winHWND);
    HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
    HBRUSH blue = CreateSolidBrush(RGB(0, 0, 255));
    initial = first;
    HWND result = NULL;
    while(initial != NULL){
        //SelectObject(dc, brush);
        //Rectangle(dc, initial->x, initial->y, initial->x + initial->width, initial->y + initial->height);
        SelectObject(dc, brush);
        Rectangle(dc, initial->x - 3, initial->y - 3, (initial->x - 3) + initial->width + 6, (initial->y - 3) + initial->height + 6);
        initial = initial->next;
    }
    DeleteDC(dc);
    DeleteObject(brush);

    initial = prev;
}

BOOL GetTextFromInputBox(WCHAR* text, UINT64 key){
    HWND hText = GetInputBoxHWNDThroughKey(key);
    if(hText == NULL) return FALSE;
    GetWindowTextW(hText, text, 16);
    return TRUE;
}