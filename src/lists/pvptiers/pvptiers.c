#include "pvptiers.h"
#include "../../result.h"
#include "../tierlists.h"








static inline VOID CalculatePoints(){
    TierInfoList* tList = ReturnTierInfoList();
    int points = 0;
    while(tList != NULL){
        switch(tList->info.peakTier){
            case 1:
                points += tList->info.peakHorL ? 44 : 60;
                break;
            case 2:
                points += tList->info.peakHorL ? 16 : 28;
                break;
            case 3:
                points += tList->info.peakHorL ? 6 : 10;
                break;
            case 4:
                points += tList->info.peakHorL ? 3 : 4;
                break;
            case 5:
                points += tList->info.peakHorL ? 1 : 2;
                break;
            default:
                break;
        }
        tList = tList->next;
    }
    SetPlayerPoints(points);
}


static inline PCHAR ReturnUrlBeginning(){
    return "https://pvptiers.com/api/rankings/";
}

static inline PCHAR ReturnName(){
    return "SubTiers";
}

VOID SetupPVPtiers(){
    TierListCallbacks cb = {0};
    cb.list = PVPTIERS;
    cb.CalculatePlayerPoints = CalculatePoints;
    cb.UrlBeginning = ReturnUrlBeginning;
    cb.ReturnName = ReturnName;
    AddTierList(cb);
}