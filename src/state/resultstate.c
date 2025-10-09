#include "resultstate.h"
#include <fileapi.h>
#include <string.h>
#include "../rguiabs.h"
#include "state.h"
#include <stdio.h>
#include <winuser.h>

typedef struct _TierArray {
    CHAR name[17];
    Tiers tierar[20];
} TierArray;

static TierArray tierar;
static INT tierAmount = 0;

char amPoints[30];


VOID BeginTier(PCHAR name){
    strcpy_s(tierar.name, 17, name);
}



VOID PlaceTier(Tiers tier){
    if(tierAmount < 0 || tierAmount > 19) return;
    strcpy_s(tierar.tierar[tierAmount].tier, 5, tier.tier);
    strcpy_s(tierar.tierar[tierAmount].tierName, 50, tier.tierName);
    strcpy_s(tierar.tierar[tierAmount].peakTier, 30, tier.peakTier);

    tierAmount++;
}

VOID PlacePoints(char* points){
    if(strlen(points) >= 30 || points == NULL){
        sprintf_s(amPoints, 30, "POINTS: ERROR");
        return;
    }
    strcpy_s(amPoints, 30, points);
}

VOID ResultState(){
    static FLOAT scroll = 0;
    static BOOL init = false;
    static Image img;
    static Texture text;
    static INT tier = -1;
    static BOOL showWin = FALSE;
    int curWin = -1;
    if(init == false){
        SetWindowTitle(tierar.name);
        CHAR temp[100];
        CHAR buffer[512];
        // we could and should use GetTempPath2A but it will make anything under Windows 11 22H2 useless
        GetTempPathA(100, temp);
        sprintf_s(buffer, 512, "%s\\mctiers\\head.png", temp);
        printf("\nHead is stored at %s, retrieving\n", buffer);
        Image image = LoadImage(buffer);
        text = LoadTextureFromImage(image);
        SetWindowIcon(image);
        init = true;
    }
    Vector2 pos = {(FLOAT)Width() / 2 - 100, (FLOAT)Height() / 2 - 500};

    if(pos.y >= 5){
        DrawTextureEx(text, pos, 0, 1, WHITE);
        RGUIDrawText(tierar.name, (INT)((FLOAT)Width() / 2 - ((FLOAT)MeasureTextEx(GetFontDefault(), tierar.name, 50, 2).x) / 2),
            (FLOAT)Height() / 2 - 300, 50, FALSE);
    } else {
        RGUIDrawText(tierar.name, (INT)((FLOAT)Width() / 2 - ((FLOAT)MeasureTextEx(GetFontDefault(), tierar.name, 50, 2).x) / 2),
           10, 50, FALSE);
    }
    
    printf("%f\n", GetMouseX() - (FLOAT)Width() / 2 - 100);
    
    UINT64 final = 0;
    if(showWin == TRUE){
        int x = Width() / 2 - 150;
        int y = Height() / 2 - 170;
        if(y < 150){
            y = 70;
        }
        int win = RGUIDrawWindow(tierar.tierar[tier].tierName, x, y, 300, 150);
        if(win == 1){
            showWin = FALSE;
        }
        RGUIDrawText(tierar.tierar[tier].tier, x + 5, y + 27, 20, FALSE);
        RGUIDrawText(tierar.tierar[tier].peakTier, x + 5, y + 47, 20, FALSE);
        int button = RGUIDrawButton("Go Back", x + 5, y + 130, 100, 20);
        if(button == 1){
            showWin = FALSE;
        }
    } else {
        INT x = 0;
        INT y = Height() / 2 - 200;
        INT shift = 300;
        if(y < 32){
            y = 70;
        }
        BOOL beginMiniMode = FALSE;
        for(INT i = 0; i < tierAmount; i++){
            int xpos = (Width() / 2) - 300 + (x * 200);
            if((Width() / 2 - shift) - 100 + (x * 200) <= 0){
                beginMiniMode = TRUE;
                xpos = 10;    
            }
            if(Width() / 2 - 100 + (x * 200) >= GetScreenWidth() - 100){
                y += 50;
                x = 0;
            }
            
            INT button = RGUIDrawButton(tierar.tierar[i].tierName, xpos, 
                    y, 200, 40);
            if(beginMiniMode == FALSE){
                if((i + 1) % 3 == 0){
                    y+=50;
                    x = 0;
                } else x++;
            } else {
                x = 0;
                y+=50;
            }
            if(button == 2){
                curWin = i;
            } 
            if(button == 1){
                showWin = TRUE;
                tier = i;
                break;
            }
            final = scroll + ((i + 2) * 80) + 30;
        }
    }
    if(curWin != -1){
        int x = GetMouseX() + 15;
        int y = GetMouseY() + 15;
        RGUIDrawWindow(tierar.tierar[curWin].tierName, x, y, 300, 100);
        RGUIDrawText(tierar.tierar[curWin].tier, x + 5, y + 27, 20, FALSE);
        RGUIDrawText(tierar.tierar[curWin].peakTier, x + 5, y + 47, 20, FALSE);
    }
    if(final == 0 && showWin == FALSE){
        RGUIDrawText("No data about this player found.....", Width() / 2 - 200, Height() / 2 - 170, 30, FALSE);
        final = scroll + 100;
    } else {
        if(!((FLOAT)Width() / 2 - 100 - GetMouseX() >= 0) && !((FLOAT)Width() / 2 - 100 - GetMouseX() <= -200)){
            if(!((FLOAT)Height() / 2 - 400 - GetMouseY() >= 0) && !((FLOAT)Height() / 2 - 400 - GetMouseY() <= -200)){
                int x = GetMouseX() + 15;
                int y = GetMouseY() + 15;
                RGUIDrawWindow(tierar.name, x, y, 300, 100);
                RGUIDrawText(tierar.name, x + 5, y + 27, 20, FALSE);
                RGUIDrawText(amPoints, x + 5, y + 47, 20, FALSE);
            }   
        }
    }
    INT button = RGUIDrawButton("Go Back", 10, 10, 70, 50);
    if(button == 1){
        ChangeState(1);
        SetWindowTitle("Native MCTiers");
        RGUISetIconToDefault();
        UnloadTexture(text);
        UnloadImage(img);
        for(int i = 0; i < tierAmount; i++){
            sprintf_s(tierar.tierar[tierAmount].tier, 5, "");
            sprintf_s(tierar.tierar[tierAmount].peakTier, 30, "");
            strcpy_s(tierar.tierar[tierAmount].tierName, 50, "");
            strcpy_s(amPoints, 30, "");
            strcpy_s(tierar.name, 16, "");
        }
        tierAmount = 0;
        init = false;
        scroll = 0;
        ChangeState(0);
    }
}

