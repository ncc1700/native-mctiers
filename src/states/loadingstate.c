#include "loadingstate.h"
#include "../rguiabs.h"
#include <wtypesbase.h>




static PCHAR animation[] = {
    "ooO",
    "Ooo",
    "oOo"
};





VOID LoadingState(){
    static INT curAnim = 0;
    static DOUBLE curTime;
    static bool init = false;
    if(init == false){
        curTime = GetTime();
        init = true;
    }
    CHAR text[] = "Getting Player Info";
    RGUIDrawText(text, 
        (GetScreenWidth() - MeasureTextEx(RGUIGetFont(), text, 20, 1).x) / 2, 
        GetScreenHeight() / 2 - 45, 20);
    RGUIDrawText(animation[curAnim], 
                    ((float)Width() / 2) - (MeasureTextEx(RGUIGetFont(), animation[curAnim], 30, 1).x) / 2, 
                    (Height() / 2), 30);
    if((GetTime() - curTime) >= 0.3){
        if(curAnim >= 2){
            curAnim = 0;
        }
        else curAnim++;
        curTime = GetTime();
    }
}