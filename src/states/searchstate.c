#include "searchstate.h"
#include "../rguiabs.h"
#include <stdio.h>
#include "../search.h"

static CHAR data[MAX_NAME_LENGTH];


PCHAR ReturnSearchInput(){
    return data;
}

VOID RenderSearchState(){
    
    CHAR titleText[] = "Search for a player";
    static INT active = 0;
    static BOOL editMode = FALSE;
    printf("%d\n", active);
    INT state = RGUIDropDownBox("MCTiers;SubTiers;PVPTiers", 10, 10, 100, 20, &active, editMode);
    if(state == 1){
        if(editMode == TRUE) editMode = FALSE;
        else editMode = TRUE;
    }
    RGUIDrawText(titleText, 
        (GetScreenWidth() - MeasureTextEx(RGUIGetFont(), titleText, 40, 1).x) / 2, 
        GetScreenHeight() / 2 - 45, 40);
    RGUIDrawTextBox(data, 
                    10, GetScreenHeight() / 2, 
                    GetScreenWidth() - 20, 25, 17, TRUE);
    int resButton = RGUIDrawButton("Search", (GetScreenWidth() - 70) / 2, GetScreenHeight() / 2 + 40, 70, 30);
    if(resButton == 1){
        BeginSearch(active);
    }
   
    
}