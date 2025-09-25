#ifndef BUTTONS_H_INCLUDED
#define BUTTONS_H_INCLUDED











#include <Windows.h>








VOID InitializeAllButtons(HWND winHWND);
VOID CreateButton(LPWSTR text, INT x, INT y, INT width, INT height, void(*CallBackFunc)(LPVOID data));
VOID CheckForAllButtonInteractionState(WPARAM wParam);







#endif