#include "tierlists.h"
#include "mctiers/mctiers.h"
#include "pvptiers/pvptiers.h"
#include "subtiers/subtiers.h"
#include "../error.h"

#include <Windows.h>
#include <stdlib.h>




static TierListCbList* list = NULL;
static TierListCbList* initial = NULL;


VOID AddTierList(TierListCallbacks callbacks){
    TierListCbList* newList = calloc(1, sizeof(TierListCbList));
    // the OS ran out of memory, will probably never be seen
    // unless for some reason the OS turns off paging/swap or
    // we run in a less capable system/OS
    if(newList == NULL){
        ErrCreateErrorWindow("Ran out of memory, might not be accurate");
        return;
    }
    newList->info.list = callbacks.list;
    newList->info.CalculatePlayerPoints = callbacks.CalculatePlayerPoints;
    newList->info.UrlBeginning = callbacks.UrlBeginning;
    newList->info.ReturnName = callbacks.ReturnName;
    if(initial == NULL){
        initial = newList;
        list = newList;
    } else {
        list->next = newList;
        list = list->next;
    }
}   


TierListCallbacks* ReturnTierList(TierLists lists){
    TierListCbList* nList = initial;

    while(nList != NULL){
        if(nList->info.list == lists){
            return &nList->info;
        }
        nList = nList->next;
    }
    return NULL;
}


VOID SetupAllTierListCallbacks(){
    SetupSubtiers();
    SetupMCtiers();
    SetupPVPtiers();
}



VOID FreeAllTierlists(){
    TierListCbList* begin = initial;
    while(begin != NULL){
        TierListCbList* next = begin->next;
        free(begin);
        begin = next;
    }
    initial = NULL;
    list = NULL;
}