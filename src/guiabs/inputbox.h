#ifndef INPUTBOX_H_INCLUDED
#define INPUTBOX_H_INCLUDED










#include <Windows.h>







VOID InitializeAllInputBoxs(HWND winHWND);
VOID CreateInputBox(LPWSTR text, INT x, INT y, INT width, INT height);
BOOL GetTextFromInputBox(WCHAR* text, UINT64 key);
VOID InitializeAllInputBoxsBackground(HWND winHWND);













#endif