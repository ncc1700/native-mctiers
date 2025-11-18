#include "result.h"
#include "error.h"
#include "osabs/osabs.h"
#include <stdlib.h>
#include <string.h>




static TierInfoList* list = NULL;
static TierInfoList* initial = NULL;
static PlayerInfo pInfo = {0};


VOID AddTier(TierInfo info){
    TierInfoList* newList = calloc(1, sizeof(TierInfoList));
    // the OS ran out of memory, will probably never be seen
    // unless for some reason the OS turns off paging/swap or
    // we run in a less capable system/OS
    if(newList == NULL){
        ErrCreateErrorWindow("Ran out of memory, result might not be accurate");
        return;
    }
    safe_strcpy(newList->info.tierName, 90, info.tierName);
    safe_strcpy(newList->info.timeGotten, 10, info.timeGotten);
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

PlayerInfo ReturnPlayerInfo(){
    return pInfo;
}

VOID SetPlayerPoints(INT points){
    pInfo.pointsReserved = points;
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