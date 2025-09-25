#include "buttons.h"
#include "states.h"
#include <wchar.h>




typedef struct _BUTTON_NODE {
    HWND hWnd;
    UINT64 key;
    WCHAR text[40];
    UINT16 x;
    UINT16 y;
    UINT16 width;
    UINT16 height;
    void(*CallBackFunc)(LPVOID data);
    struct _BUTTON_NODE* next;
    struct _BUTTON_NODE* prev;
} BUTTON_NODE;

static BUTTON_NODE* first = NULL;
static BUTTON_NODE* initial = NULL;

static inline VOID CreateButtonNode(UINT16 key, WCHAR* text, UINT16 x, UINT16 y, UINT16 width, UINT16 height, void(*CallBackFunc)(LPVOID data)){
    if(initial == NULL){
        initial = (BUTTON_NODE*)VirtualAlloc(NULL, sizeof(BUTTON_NODE), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
        initial->prev = NULL;
        initial->next = NULL;
        first = initial;
    } else {
        initial->next = (BUTTON_NODE*)VirtualAlloc(NULL, sizeof(BUTTON_NODE), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
        initial->next->prev = initial;
        initial->next->next = NULL;
        initial = initial->next;
    }
    swprintf_s(initial->text, 40, L"%s", text);
    initial->x = x;
    initial->y = y;
    initial->width = width;
    initial->height = height;
    initial->CallBackFunc = CallBackFunc;
    initial->key = key;
}


HWND GetButtonHWNDThroughKey(UINT16 key){
    BUTTON_NODE* prev = initial;
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



VOID CreateButton(LPWSTR text, INT x, INT y, INT width, INT height, void(*CallBackFunc)(LPVOID data)){
    CreateButtonNode(GetKey(), text, x, y, width, height, CallBackFunc);
}


VOID InitializeAllButtons(HWND winHWND){
    BUTTON_NODE* prev = initial;
    initial = first;
    HWND result = NULL;
    while(initial != NULL){
        if(initial->hWnd != NULL){
            initial = initial->next;
            continue;
        } 
        initial->hWnd = CreateWindowW(
            L"BUTTON",
            initial->text,
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | BS_FLAT,
            initial->x, initial->y, initial->width, initial->height, winHWND, 
            (HMENU)initial->key, (HINSTANCE)GetWindowLongPtr(winHWND, GWLP_HINSTANCE), NULL
        );
        SendMessage(initial->hWnd, WM_SETFONT, (WPARAM)GetFont(), TRUE);
        initial = initial->next;
    }
    initial = prev;
}


VOID CheckForAllButtonInteractionState(WPARAM wParam){
    BUTTON_NODE* prev = initial;
    initial = first;
    HWND result = NULL;
    while(initial != NULL){
        if(LOWORD(wParam) == initial->key && HIWORD(wParam) == BN_CLICKED){
            initial->CallBackFunc(NULL);
        }        
        initial = initial->next;
    }
    initial = prev;
}