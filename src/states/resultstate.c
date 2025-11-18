#include "resultstate.h"
#include "../result.h"
#include "../state.h"
#include <stdio.h>
#include "../rguiabs.h"
#include "searchstate.h"
#include "../osabs/osabs.h"

static inline VOID HandleScrollBar(int* offset){
    DrawRectangle(GetScreenWidth() - 20, 200, 20, GetScreenHeight() - 200, RGUIGetBackgroundColor());
    int upButtom = RGUIDrawButton("<", GetScreenWidth() - 20, 200, 20, 20);
    int downButton = RGUIDrawButton(">", GetScreenWidth() - 20, GetScreenHeight() - 20, 20, 20);
        
    if(IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)){
        if(*offset < 0) *offset += 20;
    } else if(IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)){
        *offset -= 20;
    }
    if(upButtom == 1) if(*offset < 0) *offset += 20;
    if(downButton == 1) *offset -= 20;
    int scroll = GetMouseWheelMoveV().y;
    if(scroll > 0){
       if(*offset < 0) *offset += 20;
    }
    if(scroll < 0){
       *offset -= 20;
    }
}

static inline VOID RenderPlayerInfo(PlayerInfo pInfo, Texture2D texture){
    CHAR pBuffer[255];
    safe_sprintf(pBuffer, 255, "Points: %d", pInfo.pointsReserved);
    // so we don't see the overflowing text
    DrawRectangle(0, 0, GetScreenWidth(), 200, RGUIGetBackgroundColor());
    RGUIDrawText(pInfo.name, 10, 10, 35);
    RGUIDrawText(pBuffer, 10, 60, 29);
    DrawTexture(texture, GetScreenWidth() - 200, 10, WHITE);
}

VOID ResultState(){
    static BOOL init = FALSE;
    static INT offset = 0;
    TierInfoList* list = ReturnTierInfoList();
    PlayerInfo pInfo = ReturnPlayerInfo();
    static Image image;
    static Texture2D texture;
    if(init == FALSE){
        image = LoadImage(pInfo.playerHeadPath);
        SetWindowIcon(image);
        texture = LoadTextureFromImage(image);
        init = TRUE;
    }
    DrawRectangle(0, 200, GetScreenWidth(), GetScreenHeight() - 200, BLACK);
    int i = 220;
    while(list != NULL){
        CHAR buffer[255];
        CHAR pBuffer[120];
        CHAR horl, pHorl = ' ';
        if(list->info.HorL == 1) horl = 'L';
        else horl = 'H';
        if(list->info.peakHorL == 1) pHorl = 'L';
        else pHorl = 'H';
        if(list->info.isRetired){
            safe_sprintf(buffer, 255, 
                      "%cT%d (retired)", horl, list->info.tier);
        } else {
            safe_sprintf(buffer, 255, 
                      "%cT%d (as of %s)", 
                      horl, list->info.tier, list->info.timeGotten);
        }
        safe_sprintf(pBuffer, 120, "| peak: %cT%d", pHorl, list->info.peakTier);
        int tierNameSizeX = MeasureTextEx(RGUIGetFont(), list->info.tierName, 30, 1).x;
        int bufSizeX = MeasureTextEx(RGUIGetFont(), buffer, 30, 1).x;

        DrawTextEx(RGUIGetFont(), 
                   list->info.tierName, (Vector2){10, i + offset}, 
                   30, 1, (Color){255, i - 100, 255, 255});
        DrawTextEx(RGUIGetFont(), 
                   buffer, 
                   (Vector2)
                   {tierNameSizeX + 24, i + offset}, 
                   30, 1, WHITE);
        DrawTextEx(RGUIGetFont(), 
                   pBuffer, 
                   (Vector2)
                   {bufSizeX + tierNameSizeX + 34, i + offset}, 
                   30, 1, SKYBLUE);
        
        
        DrawLine(0, (i + offset) + 40,
                 GetScreenWidth() - 20, (i + offset) + 40, WHITE);
        list = list->next;
        i += 50;
    }
    
    if(i == 220){
        DrawTextEx(RGUIGetFont(), 
                   "Nothing found......", (Vector2){10, i + offset}, 
                   40, 1, RED);
    }

    RenderPlayerInfo(pInfo, texture);
    int retButton = RGUIDrawButton("Go Back", 10, 100, 70, 30);

    // scrolling
    if(i > GetScreenHeight() || offset != 0){
        HandleScrollBar(&offset);
    }
    
    if(IsKeyPressed(KEY_P) || retButton == 1){
        RGUISetIconToDefault();
        UnloadImage(image);
        UnloadTexture(texture);
        ResetEverything();
        ClearSearchData();
        ChangeState(SEARCH_STATE);
        offset = 0;
        init = FALSE;
    }
    
}