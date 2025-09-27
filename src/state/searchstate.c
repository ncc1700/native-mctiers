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
    INT res = RGUIDropDownBox("MCTiers;PVPTiers;SubTiers", 10, 10, 100, 30, &active, edit);
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
    
    INT buttonmctiers = RGUIDrawButton("Check Rank", GetScreenWidth() / 2 - 80, GetScreenHeight() / 2 + 30, 150, 50);
    
    if(buttonmctiers == 1){
        init = FALSE;
        ChangeState(1);
        BeginSearch(searchBuffer, active);
    }
    

    // RGUIDrawText("THIS IS BETA SOFTWARE\nIF THERE IS ANY ISSUES MAKE AN ISSUE\nIN THE GITHUB\ngithub.com/vmwarehater/native-mctiers/issues", 
    //                         10, 10,30, FALSE);    
}