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
    CHAR text[15] = "Just a moment";
    // idk what i did wrong but this specifically is pissing me off, why doesn't it center normally!!!!
    RGUIDrawText(text, 
                    ((float)Width() / 2) - (MeasureTextEx(RGUIGetFont(), text, 40, 1).x) / 2, 
                    (Height() / 2) - 60, 40, FALSE);
    // like this does it normally but the one above doesn't????
    RGUIDrawText(animation[curAnim], 
                    ((float)Width() / 2) - (MeasureTextEx(RGUIGetFont(), animation[curAnim], 40, 1).x) / 2, 
                    (Height() / 2), 40, FALSE);
    if((GetTime() - curTime) >= 0.3){
        if(curAnim >= 2){
            curAnim = 0;
        }
        else curAnim++;
        curTime = GetTime();
    }
}