#ifndef TIERLISTS_H_INCLUDED
#define TIERLISTS_H_INCLUDED






#include "../types.h"
#include <stddef.h>
typedef VOID (*CalculatePlayerPointsFn)(void);
typedef PCHAR (*UrlBeginningFn)(void);
typedef PCHAR (*ReturnNameFn)(void);

typedef enum _TierLists {
    MCTIERS,
    SUBTIERS,
    PVPTIERS
} TierLists;

typedef struct _TierListCallbacks {
    TierLists list;
    CalculatePlayerPointsFn CalculatePlayerPoints;
    UrlBeginningFn UrlBeginning;
    ReturnNameFn ReturnName;
} TierListCallbacks;




typedef struct _TierListCbList {
    TierListCallbacks info;
    struct _TierListCbList* next;
} TierListCbList;


VOID AddTierList(TierListCallbacks callbacks);
TierListCallbacks* ReturnTierList(TierLists lists);
VOID SetupAllTierListCallbacks();
VOID FreeAllTierlists();




#endif