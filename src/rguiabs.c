#include "rguiabs.h"
#include "extern/raylib/raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "extern/raylib/raygui.h"

static Image img;

VOID RGUIInit(){
    img = LoadImage("resources\\img\\default.png");
    RGUISetIconToDefault();
    GuiLoadStyle("resources\\styles\\style_genesis.rgs");
}

VOID RGUISetIconToDefault(){
    SetWindowIcon(img);
}

VOID RGUIDrawText(const PCHAR text, INT x, INT y, FLOAT fontSize, BOOL isError){
    Vector2 pos = {x, y};
    Color color;
    if(isError) color = RED;
    else color = GetColor(GuiGetStyle(TEXT, TEXT_COLOR_NORMAL));
    DrawTextEx(GuiGetFont(), text, pos, fontSize, 1, color);
}

VOID RGUIDrawTextEx(const PCHAR text, INT x, INT y, FLOAT fontSize, int property, BOOL isError){
    Vector2 pos = {x, y};
    Color color;
    if(isError) color = RED;
    else color = GetColor(GuiGetStyle(TEXT, property));
    DrawTextEx(GuiGetFont(), text, pos, fontSize, 1, color);
}

Color RGUIGetBackgroundColor(){
    return GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR));
}

INT RGUIDropDownBox(const PCHAR text, INT x, INT y, INT width, INT height, int* active, BOOL editMode){
    Rectangle pos = {x, y, width, height};
    return GuiDropdownBox(pos, text, active, editMode);
}

Color RGUIGetTextColor(){
    return GetColor(GuiGetStyle(TEXT, TEXT_COLOR_NORMAL));
}

INT RGUIDrawButton(const PCHAR text, INT x, INT y, INT width, INT height){
    Rectangle pos = {x, y, width, height};
    return GuiButton(pos, text);
}

INT RGUIDrawTextBox(const PCHAR text, INT x, INT y, INT width, INT height, FLOAT fontSize, BOOL editMode){
    Rectangle pos = {x, y, width, height};
    return GuiTextBox(pos, text, fontSize, editMode);
}

INT RGUIDrawWindow(const PCHAR text, INT x, INT y, INT width, INT height){
    Rectangle pos = {x, y, width, height};
    return GuiWindowBox(pos, text);
}

INT Width(){
    return GetScreenWidth();
}

INT Height(){
    return GetScreenHeight();
}

Font RGUIGetFont(){
    return GuiGetFont();
}

VOID RGUICleanup(){
    UnloadImage(img);
}