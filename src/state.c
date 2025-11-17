#include "state.h"
#include "states/loadingstate.h"
#include "states/resultstate.h"
#include "states/searchstate.h"



static SearchType curState = SEARCH_STATE;




VOID RenderCurrentState(){
    switch(curState){
        case SEARCH_STATE:
            RenderSearchState();
            break;
        case LOADING_STATE:
            LoadingState();
            break;
        case RESULT_STATE:
            ResultState();
            break;
        default:
            curState = 0;
            break;            
    }
}

VOID ChangeState(SearchType state){
    curState = state;
}