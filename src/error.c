#include "error.h"
#include "rguiabs.h"
#include "osabs/osabs.h"
#include <stdio.h>
#include <string.h>

/*
    Taken from my other project
    code is a bit bad but needed
*/

typedef struct _ErrorWindows {
    CHAR buffer[128];
    BOOL isActive;
} ErrorWindows;

static ErrorWindows s_ErrWindows[30];
static int s_ErrWindowAmount = 0;


static inline int ErrReturnFreeWindowSpot(){
    for(int i = 0; i < s_ErrWindowAmount; i++){
        if(i >= 29) return 29;
        if(s_ErrWindows[i].isActive == false){
            return i;
        }
    }
    return s_ErrWindowAmount++;
}

VOID ErrCreateErrorWindow(const PCHAR string){
    int i = ErrReturnFreeWindowSpot();
    safe_sprintf(s_ErrWindows[i].buffer, 128, "%s", string);
    s_ErrWindows[i].isActive = true;
}

VOID ErrRenderAllErrorWindows(){
    for(int i = 0; i < s_ErrWindowAmount; i++){
        if(i >= 30) continue;
        if(s_ErrWindows[i].isActive == false) continue;
        int sizeX = MeasureTextEx(RGUIGetFont(), s_ErrWindows[i].buffer, 20, 1).x + 40;
        int sizeY = MeasureTextEx(RGUIGetFont(), s_ErrWindows[i].buffer, 20, 1).y + 100;
        int x = (GetScreenWidth() - sizeX + (i * 2)) / 2;
        int y = (GetScreenHeight() - sizeY + (i * 2)) / 2;
        int res = RGUIDrawWindow("Cyra-Editor", x, y, sizeX, sizeY);
        RGUIDrawText(s_ErrWindows[i].buffer, 
            x + 10, y + 40, 20);
        if(res == 1){
            s_ErrWindows[i].isActive = false;
        }
    }

}