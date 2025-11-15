#ifndef RESULT_H_INCLUDED
#define RESULT_H_INCLUDED










#include "extern/raylib/raylibin.h"
#include "states/searchstate.h"




typedef struct _TierInfo {
    CHAR tierName[90];
    UINT8 HorL;
    UINT8 tier;
    UINT8 peakHorL;
    UINT8 peakTier;
    BOOL isRetired;
    CHAR timeGotten[10];
} TierInfo;

typedef struct _PlayerInfo {
    CHAR name[MAX_NAME_LENGTH];
    CHAR playerHeadPath[256];
    UINT8 pointsReserved;
} PlayerInfo;


typedef struct _TierInfoList {
    TierInfo info;
    struct _TierInfoList* next;
} TierInfoList;





VOID AddTier(TierInfo info);
VOID SetupPlayerInfo(PlayerInfo info);
VOID CalculatePlayerPoints();
PlayerInfo ReturnPlayerInfo();
TierInfoList* ReturnTierInfoList();
VOID ResetEverything();

#endif