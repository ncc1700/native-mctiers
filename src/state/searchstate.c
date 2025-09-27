#include "searchstate.h"
#include "state.h"
#include "../rguiabs.h"
#include "../search/search.h"
#include <handleapi.h>
#include <libloaderapi.h>
#include <minwindef.h>
#include <stdio.h>
#include <shellapi.h>
#include <winuser.h>

char searchBuffer[17];

VOID SearchState(){
    static BOOL init = FALSE;
    if(init == FALSE){
        init = TRUE;
    }
    static BOOL edit = FALSE;
    static INT active;
    RGUIDrawText("Search at:", 10, 10, 30, FALSE);
    INT res = RGUIDropDownBox("MCTiers;PVPTiers;SubTiers", 150, 10, 100, 35, &active, edit);
    if(res == 1){
        if(edit == FALSE) edit = TRUE;
        else edit = FALSE;
    }
    char search[25] = "Check for a players rank";
    RGUIDrawText(search, 
        (FLOAT)GetScreenWidth() / 2 - MeasureTextEx(RGUIGetFont(), search, 50, 1).x + 240, 
        (FLOAT)GetScreenHeight() / 2 - 100, 50, FALSE);
        
    INT box = RGUIDrawTextBox(searchBuffer, 35, GetScreenHeight() / 2 - 30, Width() - 70, 40, 30, TRUE);
    if(strlen(searchBuffer) >= 17){
        sprintf_s(searchBuffer, 17, "");
    }
    
    INT button = RGUIDrawButton("Check Rank", GetScreenWidth() / 2 - 80, GetScreenHeight() / 2 + 30, 150, 50);
    
    if(button == 1 || IsKeyPressed(KEY_ENTER)){
        init = FALSE;
        ChangeState(1);
        BeginSearch(searchBuffer, active);
    }
    
    if(button == 2){
        int x = GetMouseX() + 10;
        int y = GetMouseY() + 10;
        RGUIDrawWindow("Test Window for something else...", x, y, 300, 100);
        RGUIDrawText("will be used in our lovely\nresult page very soon ;)", x + 40, y + 40, 20, FALSE);
    }
    // RGUIDrawText("THIS IS BETA SOFTWARE\nIF THERE IS ANY ISSUES MAKE AN ISSUE\nIN THE GITHUB\ngithub.com/vmwarehater/native-mctiers/issues", 
    //                         10, 10,30, FALSE);    
}