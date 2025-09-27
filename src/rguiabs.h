#ifndef RGUIABS_H_INCLUDED
#define RGUIABS_H_INCLUDED




#include "typedef.h"

#include "extern/raylib/raylib.h"
#include "extern/raylib/raygui.h"


VOID RGUIInit();
VOID RGUISetIconToDefault();
VOID RGUIDrawText(const PCHAR text, INT x, INT y, FLOAT fontSize, BOOL isError);
VOID RGUIDrawTextEx(const PCHAR text, INT x, INT y, FLOAT fontSize, int property, BOOL isError);
Color RGUIGetBackgroundColor();
INT RGUIDropDownBox(const PCHAR text, INT x, INT y, INT width, INT height, int* active, BOOL editMode);
Color RGUIGetTextColor();
INT RGUIDrawButton(const PCHAR text, INT x, INT y, INT width, INT height);
INT RGUIDrawTextBox(const PCHAR text, INT x, INT y, INT width, INT height, FLOAT fontSize, BOOL editMode);
INT RGUIDrawWindow(const PCHAR text, INT x, INT y, INT width, INT height);
INT Width();
INT Height();
Font RGUIGetFont();
VOID RGUICleanup();

#endif