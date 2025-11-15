#include "result.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>




static TierInfoList* list = NULL;
static TierInfoList* initial = NULL;
static PlayerInfo pInfo = {0};


VOID AddTier(TierInfo info){
    TierInfoList* newList = calloc(1, sizeof(TierInfoList));
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

VOID CalculatePlayerPoints(){
    // STUB
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
        TierInfoList* cur = begin;
        begin = begin->next;
        free(cur);
    }
    initial = NULL;
    list = NULL;
    pInfo = (PlayerInfo){0};
}