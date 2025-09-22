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
    static Texture2D mctierstext;
    static Texture2D pvptierstext;
    static Texture2D subtierstext;
    static BOOL init = FALSE;
    if(init == FALSE){
        mctierstext = LoadTexture("resources/img/mctiers/mctiers.png");
        pvptierstext = LoadTexture("resources/img/mctiers/pvptiers.png");
        subtierstext = LoadTexture("resources/img/mctiers/subtiers.png");
        init = TRUE;
    }
    static BOOL edit = TRUE;
    char search[21] = "Search for a player";
    RGUIDrawText(search, 
        GetScreenWidth() / 2 - MeasureTextEx(RGUIGetFont(), search, 50, 1).x + 190, 
        GetScreenHeight() / 2 - 100, 50, FALSE);
        
    INT box = RGUIDrawTextBox(searchBuffer, 35, GetScreenHeight() / 2 - 30, Width() - 70, 40, 30, edit);
    if(strlen(searchBuffer) >= 17){
        sprintf_s(searchBuffer, 17, "");
    }
    
    INT buttonmctiers = RGUIDrawButton("Search (MCTIERS)", GetScreenWidth() / 2 - 240, GetScreenHeight() / 2 + 30, 150, 50);
    
    if(buttonmctiers == 1){
        UnloadTexture(mctierstext);
        UnloadTexture(pvptierstext);
        UnloadTexture(subtierstext);
        init = FALSE;
        ChangeState(1);
        BeginSearch(searchBuffer, 0);
    }

    if(buttonmctiers == 2){
        DrawTexture(mctierstext, GetScreenWidth() - 530, GetScreenHeight() - 110, GRAY);
    }
    
    INT buttonpvptiers = RGUIDrawButton("Search (PVPTIERS)", GetScreenWidth() / 2 + 80, GetScreenHeight() / 2 + 30, 150, 50);
    if(buttonpvptiers == 1){
        UnloadTexture(mctierstext);
        UnloadTexture(pvptierstext);
        UnloadTexture(subtierstext);
        init = FALSE;
        ChangeState(1);
        BeginSearch(searchBuffer, 1);
    }

    if(buttonpvptiers == 2){
        DrawTextureEx(pvptierstext, (Vector2){GetScreenWidth() - 230, GetScreenHeight() - 230}, 0, 0.1, GRAY);
    }

    INT buttonsubtiers = RGUIDrawButton("Search (SUBTIERS)", GetScreenWidth() / 2 - 80, GetScreenHeight() / 2 + 30, 150, 50);
    if(buttonsubtiers == 1){
        UnloadTexture(mctierstext);
        UnloadTexture(pvptierstext);
        UnloadTexture(subtierstext);
        init = FALSE;
        ChangeState(1);
        BeginSearch(searchBuffer, 2);
    }

    if(buttonsubtiers == 2){
        DrawTextureEx(subtierstext, (Vector2){GetScreenWidth() - 290, GetScreenHeight() - 260}, 0, 10, GRAY);
    }


    RGUIDrawText("THIS IS BETA SOFTWARE\nIF THERE IS ANY ISSUES MAKE AN ISSUE\nIN THE GITHUB\ngithub.com/vmwarehater/native-mctiers/issues", 
                            10, 10,30, FALSE);    
}