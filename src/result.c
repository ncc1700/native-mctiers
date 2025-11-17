#include "result.h"
#include <stdlib.h>
#include <string.h>
#include <winuser.h>




static TierInfoList* list = NULL;
static TierInfoList* initial = NULL;
static PlayerInfo pInfo = {0};


VOID AddTier(TierInfo info){
    TierInfoList* newList = calloc(1, sizeof(TierInfoList));
    // did the OS run out of memory, will probably never be seen
    // unless for some reason the OS turns off paging/swap or
    // we run in a less capable system/OS
    if(newList == NULL){
        MessageBoxW(NULL, L"Ran out of memory, result might not be accurate",
                    L"Native MCTiers", MB_OK | MB_ICONERROR);
        return;
    }
    strcpy_s(newList->info.tierName, 90, info.tierName);
    strcpy_s(newList->info.timeGotten, 10, info.timeGotten);
    newList->info.tier = info.tier;
    newList->info.HorL = info.HorL;
    newList->info.isRetired = info.isRetired;
    newList->info.peakHorL = info.peakHorL;
    newList->info.peakTier = info.peakTier;
    if(initial == NULL){
        initial = newList;
        list = newList;
    } else {
        list->next = newList;
        list = list->next;
    }
}   


VOID SetupPlayerInfo(PlayerInfo info){
    memcpy_s(&pInfo, 
             sizeof(PlayerInfo), 
             &info, 
             sizeof(PlayerInfo));
}

static inline VOID CalculateMCTiersPlayerPoints(){
    TierInfoList* tList = initial;
    while(tList != NULL){
        switch(tList->info.peakTier){
            case 1:
                pInfo.pointsReserved += tList->info.peakHorL ? 45 : 60;
                break;
            case 2:
                pInfo.pointsReserved += tList->info.peakHorL ? 20 : 30;
                break;
            case 3:
                pInfo.pointsReserved += tList->info.peakHorL ? 6 : 10;
                break;
            case 4:
                pInfo.pointsReserved += tList->info.peakHorL ? 3 : 4;
                break;
            case 5:
                pInfo.pointsReserved += tList->info.peakHorL ? 1 : 2;
                break;
            default:
                break;
        }
        tList = tList->next;
    }
}

static inline VOID CalculateSubTiersPlayerPoints(){
    TierInfoList* tList = initial;
    while(tList != NULL){
        switch(tList->info.peakTier){
            case 1:
                pInfo.pointsReserved += tList->info.peakHorL ? 45 : 60;
                break;
            case 2:
                pInfo.pointsReserved += tList->info.peakHorL ? 20 : 30;
                break;
            case 3:
                pInfo.pointsReserved += tList->info.peakHorL ? 6 : 10;
                break;
            case 4:
                pInfo.pointsReserved += tList->info.peakHorL ? 3 : 4;
                break;
            case 5:
                pInfo.pointsReserved += tList->info.peakHorL ? 1 : 2;
                break;
            default:
                break;
        }
        tList = tList->next;
    }
}

static inline VOID CalculatePVPTiersPlayerPoints(){
    // stub
    pInfo.pointsReserved = 0;
}

VOID CalculatePlayerPoints(int tierSystem){
    switch(tierSystem){
        case 0:
            CalculateMCTiersPlayerPoints();
            return;
        case 1:
            CalculateSubTiersPlayerPoints();
            return;
        case 2:
            CalculatePVPTiersPlayerPoints();
            return;
    }
}

PlayerInfo ReturnPlayerInfo(){
    return pInfo;
}

TierInfoList* ReturnTierInfoList(){
    return initial;
}


VOID ResetEverything(){
    TierInfoList* begin = initial;
    while(begin != NULL){
        TierInfoList* next = begin->next;
        free(begin);
        begin = next;
    }
    initial = NULL;
    list = NULL;
    pInfo = (PlayerInfo){0};
}