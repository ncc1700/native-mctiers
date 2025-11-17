#include "resultstate.h"
#include "../result.h"
#include "../state.h"
#include <stdio.h>
#include <winnt.h>
#include "../rguiabs.h"


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
    sprintf_s(pBuffer, 255, "Points: %d", pInfo.pointsReserved);
    
    // so we don't see the overflowing text
    DrawRectangle(0, 0, GetScreenWidth(), 200, RGUIGetBackgroundColor());
    RGUIDrawText(pInfo.name, 10, 10, 40);
    RGUIDrawText(pBuffer, 10, 60, 26);
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
        CHAR horl, pHorl = ' ';
        if(list->info.HorL == 1) horl = 'L';
        else horl = 'H';
        if(list->info.peakHorL == 1) pHorl = 'L';
        else pHorl = 'H';
        if(list->info.isRetired){
            sprintf_s(buffer, 255, 
                      "%cT%d, peak: %cT%d | (retired)", horl, list->info.tier, pHorl, list->info.peakTier);
        } else {
            sprintf_s(buffer, 255, 
                      "%cT%d, peak: %cT%d (as of %s)", 
                      horl, list->info.tier, pHorl, list->info.peakTier, list->info.timeGotten);
        }
        DrawTextEx(RGUIGetFont(), 
                   list->info.tierName, (Vector2){10, i + offset}, 
                   26, 1, (Color){255, i - 100, 255, 255});
        DrawTextEx(RGUIGetFont(), 
                   buffer, 
                   (Vector2)
                   {MeasureTextEx(RGUIGetFont(), list->info.tierName, 26, 1).x + 20, i + offset}, 
                   26, 1, WHITE);
        
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

    // scroll bar
    if(i > GetScreenHeight() || offset != 0){
        HandleScrollBar(&offset);
    }
    

    if(IsKeyPressed(KEY_P) || retButton == 1){
        RGUISetIconToDefault();
        UnloadImage(image);
        UnloadTexture(texture);
        ResetEverything();
        ChangeState(SEARCH_STATE);
        offset = 0;
        init = FALSE;
    }
    
}