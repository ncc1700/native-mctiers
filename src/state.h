#ifndef STATE_H_INCLUDED
#define STATE_H_INCLUDED










#include "types.h"

typedef enum _SearchType {
    SEARCH_STATE,
    LOADING_STATE,
    RESULT_STATE
} SearchType;


VOID RenderCurrentState();
VOID ChangeState(SearchType state);








#endif