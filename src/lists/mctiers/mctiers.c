#include "mctiers.h"
#include "../../result.h"
#include "../tierlists.h"








static inline VOID CalculatePoints(){
    TierInfoList* tList = ReturnTierInfoList();
    INT points = 0;
    while(tList != NULL){
        switch(tList->info.peakTier){
            case 1:
                points += tList->info.peakHorL ? 45 : 60;
                break;
            case 2:
                points += tList->info.peakHorL ? 20 : 30;
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
    return "https://mctiers.com/api/rankings/";
}

static inline PCHAR ReturnName(){
    return "SubTiers";
}

VOID SetupMCtiers(){
    TierListCallbacks cb = {0};
    cb.list = MCTIERS;
    cb.CalculatePlayerPoints = CalculatePoints;
    cb.UrlBeginning = ReturnUrlBeginning;
    cb.ReturnName = ReturnName;
    AddTierList(cb);
}