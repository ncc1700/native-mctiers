#ifndef RESULT_H_INCLUDED
#define RESULT_H_INCLUDED










#include "types.h"
#include "states/searchstate.h"




typedef struct _TierInfo {
    CHAR tierName[90];
    UINT8 HorL;
    UINT8 tier;
    UINT8 peakHorL;
    UINT8 peakTier;
    BOOL isRetired;
    CHAR timeGotten[32];
} TierInfo;

typedef struct _PlayerInfo {
    CHAR name[MAX_NAME_LENGTH];
    CHAR playerHeadPath[256];
    UINT32 pointsReserved;
} PlayerInfo;


typedef struct _TierInfoList {
    TierInfo info;
    struct _TierInfoList* next;
} TierInfoList;





VOID AddTier(TierInfo info);
VOID SetupPlayerInfo(PlayerInfo info);
PlayerInfo ReturnPlayerInfo();
VOID SetPlayerPoints(INT points);
TierInfoList* ReturnTierInfoList();
VOID ResetEverything();

#endif