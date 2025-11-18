#include "search.h"
#include "error.h"
#include "extern/naett/naett.h"
#include "extern/tinycthread/tinycthread.h"
#include "osabs/osabs.h"
#include "result.h"
#include "state.h"
#include "states/searchstate.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "extern/yyjson/yyjson.h"
#include "lists/tierlists.h"

#ifdef _WIN32
#include <Windows.h>
#elif __linux__
#include <unistd.h>
#endif
static UINT8 sWhere = 0;
static CHAR uuid[40] = {0};
static CHAR headPath[255] = {0};

#define URL_SIZE 255

static inline void os_sleep(int seconds){
    #ifdef _WIN32
    Sleep(seconds * 1000);
    #elif __linux__
    sleep(seconds);
    #endif
}


static inline BOOL FillUUID(PCHAR username){
    CHAR url[URL_SIZE];
    safe_sprintf(url, URL_SIZE, "https://api.mojang.com/users/profiles/minecraft/%s", username);
    naettReq* req = naettRequestWithOptions(url, 0, NULL);
    naettRes* res = naettMake(req);
    while(!naettComplete(res)){
        printf("waiting on mojang...\n");
        os_sleep(1);
    }
    if(naettGetStatus(res) < 0){
        return FALSE;
    }
    int bodyLength = 0;
    const PCHAR body = (const PCHAR)naettGetBody(res, &bodyLength);
    if(body == NULL) return FALSE;
    printf("%s\n", body);
    
    yyjson_doc* jsonDoc = yyjson_read(body, bodyLength, 0);
    if(jsonDoc == NULL) return FALSE;
    yyjson_val* value = yyjson_doc_get_root(jsonDoc);
    if(value == NULL) return FALSE;
    yyjson_val* getUUID = yyjson_obj_get(value, "id");
    if(getUUID == NULL) return FALSE;
    safe_sprintf(uuid, 40, "%s", yyjson_get_str(getUUID));
    yyjson_doc_free(jsonDoc);
    free((void*)body);
    return TRUE;
}


static inline BOOL GetPlayerHead(PCHAR username){
    CHAR url[URL_SIZE];
    safe_sprintf(url, URL_SIZE, "https://www.mc-heads.net/head/%s", username);


    naettReq* req = naettRequestWithOptions(url, 0, NULL);
    naettRes* res = naettMake(req);
    while(!naettComplete(res)){
        printf("waiting on mc-heads...\n");
        os_sleep(1);
    }
    if(naettGetStatus(res) < 0){
        return FALSE;
    }
    int bodyLength = 0;
    void* body = (void*)naettGetBody(res, &bodyLength);
    printf("head image size is %d\n", bodyLength);


    CHAR headpath[255];
    safe_sprintf(headpath, 255, "head.png");
    printf("\nHead is going to be stored at %s\n", headpath);

   
    // yes i ran out of names
    safe_sprintf(headpath, 255, "%s", headpath);
    FILE* fp = fopen(headpath, "wb");
    if(!fp){
        return FALSE;
    }
    fwrite(body, bodyLength, 1, fp);
    fclose(fp);
    free((void*)body);
    return TRUE;
}

static INT SearchThreadEntry(){
    if(FillUUID(ReturnSearchInput()) == FALSE){
        ErrCreateErrorWindow("Invalid Name");
        ChangeState(SEARCH_STATE);
        return 1;
    }
    if(GetPlayerHead(ReturnSearchInput()) == FALSE){
        ErrCreateErrorWindow("Couldn't get Player Head");
        ChangeState(SEARCH_STATE);
        return 1;
    }

    
    PlayerInfo info;
    safe_sprintf(info.name, 17, "%s", ReturnSearchInput());
    safe_sprintf(info.playerHeadPath, 255, "%s", headPath);
    info.pointsReserved = 0;
    SetupPlayerInfo(info);

    // format because theres three (3) (yes three) sites where people check their tiers
    CHAR url[URL_SIZE];
    // if(sWhere == 0){
    //     safe_sprintf(url, URL_SIZE, "https://mctiers.com/api/rankings/%s", uuid);
    // } else if(sWhere == 1){
    //     safe_sprintf(url, URL_SIZE, "https://subtiers.net/api/rankings/%s", uuid);
    // } else {
    //     safe_sprintf(url, URL_SIZE, "https://pvptiers.com/api/rankings/%s", uuid);
    // }
    safe_sprintf(url, URL_SIZE, "%s%s", 
                ReturnTierList(sWhere)->UrlBeginning(), uuid);
    naettReq* req = naettRequestWithOptions(url, 0, NULL);
    naettRes* res = naettMake(req);
    while(naettComplete(res) == FALSE){
        printf("waiting on tierlist site...\n");
        os_sleep(1);
    }
    int bodyLength;
    PCHAR body = (PCHAR)naettGetBody(res, &bodyLength);

    yyjson_doc* jsonDoc = yyjson_read(body, bodyLength, 0);
    if(jsonDoc == NULL){
        ErrCreateErrorWindow("Couldn't parse body, does the player exist in this tierlist?");
        free((void*)body);
        ChangeState(SEARCH_STATE);
        return 1;
    }
    yyjson_val* root = yyjson_doc_get_root(jsonDoc);
    
    if(root == NULL){
        ErrCreateErrorWindow("Couldn't find root!");
        yyjson_doc_free(jsonDoc);
        free((void*)body);
        ChangeState(SEARCH_STATE);
        return 1;
    }
    size_t idx, max;
    yyjson_val *main, *tier;
    yyjson_obj_foreach(root, idx, max, main, tier) {
        TierInfo tInfo = {0};
        if(main == NULL || tier == NULL){
            ErrCreateErrorWindow("Main or Tier is NULL");
            yyjson_doc_free(jsonDoc);
            free((void*)body);
            ChangeState(SEARCH_STATE);
            return 1;
        }
        yyjson_val* curTier = yyjson_obj_get(tier, "tier");
        yyjson_val* horl = yyjson_obj_get(tier, "pos");
        yyjson_val* peak_tier = yyjson_obj_get(tier, "peak_tier");
        yyjson_val* peakhorl = yyjson_obj_get(tier, "peak_pos");
        yyjson_val* isRetired = yyjson_obj_get(tier, "retired");
        yyjson_val* attained = yyjson_obj_get(tier, "attained");
        if(curTier == NULL || horl == NULL || peak_tier == NULL 
                || peakhorl == NULL || isRetired == NULL || attained == NULL)
        {
            ErrCreateErrorWindow("Error parsing JSON");
            yyjson_doc_free(jsonDoc);
            free((void*)body);
            ChangeState(SEARCH_STATE);
            return 1;
        }
        // before we do anything fun and easy, lets get the time out of our way
        struct tm *lt;
        time_t timet = (time_t)yyjson_get_sint(attained);
        lt = localtime(&timet);
        if(lt != NULL){
            size_t result = 0;
            #ifdef _WIN32
            result = strftime(tInfo.timeGotten, 32, "%D", lt);
            #elif __linux__
            result = strftime(tInfo.timeGotten, 32, "%D", lt);
            #endif
            if(result == 0){
                printf("ERROR, COULDN'T GET TIME!\n");
                safe_sprintf(tInfo.timeGotten, 32, "UNKNOWN");
            }
        } else {
            printf("ERROR, COULDN'T GET LOCALTIME!\n");
            safe_sprintf(tInfo.timeGotten, 32, "UNKNOWN");
        }
        printf("%s\n", yyjson_get_str(main));
        safe_sprintf(tInfo.tierName, 90, "%s", yyjson_get_str(main));
        tInfo.tier = yyjson_get_int(curTier);
        tInfo.HorL = yyjson_get_int(horl);
        tInfo.peakTier = yyjson_get_int(peak_tier);
        tInfo.peakHorL = yyjson_get_int(peakhorl);
        tInfo.isRetired = yyjson_get_bool(isRetired);
        AddTier(tInfo);
    }
    ReturnTierList(sWhere)->CalculatePlayerPoints();
    yyjson_doc_free(jsonDoc);
    free((void*)body);
    ChangeState(RESULT_STATE);
    return 0;
}






VOID BeginSearch(UINT8 where){
    sWhere = where;
    ChangeState(LOADING_STATE);
    thrd_t thrd;
    thrd_create(&thrd, SearchThreadEntry, NULL);
}