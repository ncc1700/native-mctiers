#ifndef RESULTSTATE_H_INCLUDED
#define RESULTSTATE_H_INCLUDED









#include "../typedef.h"

typedef struct _Tiers {
    char tierName[50];
    char tier[5];
    char peakTier[30];
} Tiers;

VOID BeginTier(PCHAR name);
VOID PlaceTier(Tiers tier);
VOID PlacePoints(char* points);
VOID ResultState();






#endif