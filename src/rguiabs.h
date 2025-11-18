#ifndef RGUIABS_H_INCLUDED
#define RGUIABS_H_INCLUDED




#include "extern/raylib/raylibin.h"
#include "types.h"


VOID RGUIInit(char* style);
VOID RGUISetIconToDefault();
VOID RGUIDrawText(const PCHAR text, INT x, INT y, FLOAT fontSize);
VOID RGUIDrawTextEx(const PCHAR text, INT x, INT y, FLOAT fontSize, int property, BOOL isError);
Color RGUIGetBackgroundColor();
INT RGUIDropDownBox(const PCHAR text, INT x, INT y, INT width, INT height, int* active, BOOL editMode);
Color RGUIGetTextColor();
Color RGUIGetTextColorWhenFocused();
INT RGUIDrawButton(const PCHAR text, INT x, INT y, INT width, INT height);
INT RGUIDrawTextBox(const PCHAR text, INT x, INT y, INT width, INT height, FLOAT textAmount, BOOL editMode);
INT RGUIDrawWindow(const PCHAR text, INT x, INT y, INT width, INT height);
INT Width();
INT Height();
Font RGUIGetFont();
VOID RGUICleanup();

#endif