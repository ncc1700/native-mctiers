#ifndef STATES_H_INCLUDED
#define STATES_H_INCLUDED









#include <Windows.h>






UINT64 GetKey();
HFONT GetFont();
VOID SetupGui();
VOID EndGui();
UINT64 Width();
UINT64 Height();
VOID SetWidth(UINT64 newWidth);
VOID SetHeight(UINT64 newHeight);
VOID RepaintWindow(HWND hWnd);



#endif