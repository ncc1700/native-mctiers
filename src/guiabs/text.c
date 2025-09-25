#include "text.h"
#include "states.h"
#include <wchar.h>




typedef struct _TEXT_NODE {
    HWND hWnd;
    UINT64 key;
    WCHAR text[512];
    UINT16 x;
    UINT16 y;
    UINT16 width;
    UINT16 height;
    struct _TEXT_NODE* next;
    struct _TEXT_NODE* prev;
} TEXT_NODE;

static TEXT_NODE* first = NULL;
static TEXT_NODE* initial = NULL;

static inline VOID CreateTextNode(UINT16 key, WCHAR* text, UINT16 x, UINT16 y, UINT16 width, UINT16 height){
    if(initial == NULL){
        initial = (TEXT_NODE*)VirtualAlloc(NULL, sizeof(TEXT_NODE), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
        initial->prev = NULL;
        initial->next = NULL;
        first = initial;
    } else {
        initial->next = (TEXT_NODE*)VirtualAlloc(NULL, sizeof(TEXT_NODE), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
        initial->next->prev = initial;
        initial->next->next = NULL;
        initial = initial->next;
    }
    swprintf_s(initial->text, 512, L"%s", text);
    initial->x = x;
    initial->y = y;
    initial->width = width;
    initial->height = height;
    initial->key = key;
}


HWND GetTextHWNDThroughKey(UINT16 key){
    TEXT_NODE* prev = initial;
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



VOID CreateText(LPWSTR text, INT x, INT y, INT width, INT height){
    CreateTextNode(GetKey(), text, x, y, width, height);
}


VOID InitializeAllTexts(HWND winHWND){
    TEXT_NODE* prev = initial;
    initial = first;
    HWND result = NULL;
    while(initial != NULL){
        HDC dc = GetDC(winHWND);
        SetBkMode(dc, TRANSPARENT);
        SelectObject(dc, GetFont());
        TextOutW(dc, initial->x, initial->y, initial->text, wcslen(initial->text));
        DeleteDC(dc);
        initial = initial->next;
    }
    initial = prev;
}


