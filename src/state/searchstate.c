#include "searchstate.h"
#include "state.h"
#include "../search/search.h"
#include <handleapi.h>
#include <libloaderapi.h>
#include <minwindef.h>
#include <stdio.h>
#include <shellapi.h>
#include <winuser.h>

char searchBuffer[17];



VOID SearchState(){
    // static Texture2D mctierstext;
    // static Texture2D pvptierstext;
    // static Texture2D subtierstext;
    // static BOOL init = FALSE;
    // if(init == FALSE){
    //     // will be used later
    //     init = TRUE;
    // }
    // static BOOL edit = TRUE;
    // char search[21] = "Search for a player";
    // RGUIDrawText(search, 
    //     GetScreenWidth() / 2 - MeasureTextEx(RGUIGetFont(), search, 50, 1).x + 190, 
    //     GetScreenHeight() / 2 - 100, 50, FALSE);
        
    // INT box = RGUIDrawTextBox(searchBuffer, 35, GetScreenHeight() / 2 - 30, Width() - 70, 40, 30, edit);
    // if(strlen(searchBuffer) >= 17){
    //     sprintf_s(searchBuffer, 17, "");
    // }
    
    // INT buttonmctiers = RGUIDrawButton("Search (MCTIERS)", GetScreenWidth() / 2 - 240, GetScreenHeight() / 2 + 30, 150, 50);
    
    // if(buttonmctiers == 1){
    //     init = FALSE;
    //     ChangeState(1);
    //     BeginSearch(searchBuffer, 0);
    // }

   
    
    // INT buttonpvptiers = RGUIDrawButton("Search (PVPTIERS)", GetScreenWidth() / 2 + 80, GetScreenHeight() / 2 + 30, 150, 50);
    // if(buttonpvptiers == 1){
    //     init = FALSE;
    //     ChangeState(1);
    //     BeginSearch(searchBuffer, 1);
    // }

   
    // INT buttonsubtiers = RGUIDrawButton("Search (SUBTIERS)", GetScreenWidth() / 2 - 80, GetScreenHeight() / 2 + 30, 150, 50);
    // if(buttonsubtiers == 1){
    //     init = FALSE;
    //     ChangeState(1);
    //     BeginSearch(searchBuffer, 2);
    // }



    // RGUIDrawText("THIS IS BETA SOFTWARE\nIF THERE IS ANY ISSUES MAKE AN ISSUE\nIN THE GITHUB\ngithub.com/vmwarehater/native-mctiers/issues", 
    //                         10, 10,30, FALSE);    
}