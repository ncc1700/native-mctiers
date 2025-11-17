#include "search.h"
#include "extern/naett/naett.h"
#include "result.h"
#include "state.h"
#include "states/searchstate.h"
#include <stdio.h>
#include <stdlib.h>
#include <Shlwapi.h>
#include <winuser.h>
#include <time.h>
#include "extern/yyjson/yyjson.h"
static UINT8 sWhere = 0;
static CHAR uuid[40] = {0};
static CHAR headPath[255] = {0};

#define URL_SIZE 255



static inline BOOL FillUUID(PCHAR username){
    CHAR url[URL_SIZE];
    sprintf_s(url, URL_SIZE, "https://api.mojang.com/users/profiles/minecraft/%s", username);
    naettReq* req = naettRequestWithOptions(url, 0, NULL);
    naettRes* res = naettMake(req);
    while(!naettComplete(res)){
        printf("waiting on mojang...\n");
        Sleep(500);
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
    sprintf_s(uuid, 40, "%s", yyjson_get_str(getUUID));
    yyjson_doc_free(jsonDoc);
    free((void*)body);
    return TRUE;
}


static inline BOOL GetPlayerHead(PCHAR username){
    CHAR url[URL_SIZE];
    sprintf_s(url, URL_SIZE, "https://www.mc-heads.net/head/%s", username);


    naettReq* req = naettRequestWithOptions(url, 0, NULL);
    naettRes* res = naettMake(req);
    while(!naettComplete(res)){
        printf("waiting on mc-heads...\n");
        Sleep(500);
    }
    if(naettGetStatus(res) < 0){
        return FALSE;
    }
    int bodyLength = 0;
    void* body = (void*)naettGetBody(res, &bodyLength);
    printf("head image size is %d\n", bodyLength);


    CHAR temppath[100];
    // TODO: in like 10 years use GetTempPath2A when everyone is on 11 or up
    GetTempPathA(100, temppath);
    CHAR headpath[255];
    sprintf_s(headpath, 255, "%s\\mctiers\\head.png", temppath);
    printf("\nHead is going to be stored at %s\n", headpath);

    // we use this to check if the path even exists, if not we create it
    // yes ik useless and for one case but idrc
    CHAR path[255];
    sprintf_s(path, 255, "%s\\mctiers", temppath);
    if(!PathFileExistsA(path)){
        CreateDirectoryA(path, NULL);
    }

    // yes i ran out of names
    strcpy_s(headPath, 255, headpath);
    HANDLE hFile = CreateFileA(headpath, GENERIC_READ | GENERIC_WRITE, 0, NULL,
                                CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL , NULL);
    if(hFile == INVALID_HANDLE_VALUE){
        printf("failed with status of %lu\n", GetLastError());
        return FALSE;
    }
    BOOL result = WriteFile(hFile, body, bodyLength, NULL, NULL);
    if(result == FALSE){
        return FALSE;
    }
    CloseHandle(hFile);
    free((void*)body);
    return TRUE;
}

static DWORD WINAPI SearchThreadEntry(){
    if(FillUUID(ReturnSearchInput()) == FALSE){
        MessageBoxW(NULL, L"Invalid Name",
                    L"Native MCTiers", MB_OK | MB_ICONERROR);
        ChangeState(SEARCH_STATE);
        return 1;
    }
    if(GetPlayerHead(ReturnSearchInput()) == FALSE){
        MessageBoxW(NULL, L"Error: Couldn't obtain player head",
                    L"Native MCTiers", MB_OK | MB_ICONERROR);
        ChangeState(SEARCH_STATE);
        return 1;
    }

    
    PlayerInfo info;

    strcpy_s(info.name, 17, ReturnSearchInput());
    strcpy_s(info.playerHeadPath, 255, headPath);
    info.pointsReserved = 0;
    SetupPlayerInfo(info);

    // format because theres three (3) (yes three) sites where people check their tiers
    CHAR url[URL_SIZE];
    if(sWhere == 0){
        sprintf_s(url, URL_SIZE, "https://mctiers.com/api/rankings/%s", uuid);
    } else if(sWhere == 1){
        sprintf_s(url, URL_SIZE, "https://subtiers.net/api/rankings/%s", uuid);
    } else {
        sprintf_s(url, URL_SIZE, "https://pvptiers.com/api/rankings/%s", uuid);
    }

    naettReq* req = naettRequestWithOptions(url, 0, NULL);
    naettRes* res = naettMake(req);
    while(naettComplete(res) == FALSE){
        printf("waiting on tierlist site...\n");
        Sleep(500);
    }
    int bodyLength;
    PCHAR body = (PCHAR)naettGetBody(res, &bodyLength);

    yyjson_doc* jsonDoc = yyjson_read(body, bodyLength, 0);
    if(jsonDoc == NULL){
        MessageBoxW(NULL, L"Couldn't parse body, does the player exist in this tierlist?",
                    L"Native MCTiers", MB_OK | MB_ICONERROR);
        free((void*)body);
        ChangeState(SEARCH_STATE);
        return 1;
    }
    yyjson_val* root = yyjson_doc_get_root(jsonDoc);
    
    if(root == NULL){
        MessageBoxW(NULL, L"Couldn't find root",
                    L"Native MCTiers", MB_OK | MB_ICONERROR);
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
            MessageBoxW(NULL, L"main or tier is null",
                        L"Native MCTiers", MB_OK | MB_ICONERROR);
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
            MessageBoxW(NULL, L"Error parsing json",
                        L"Native MCTiers", MB_OK | MB_ICONERROR);
            yyjson_doc_free(jsonDoc);
            free((void*)body);
            ChangeState(SEARCH_STATE);
            return 1;
        }
        // before we do anything fun and easy, lets get the time out of our way
        struct tm lt;
        time_t timet = (time_t)yyjson_get_sint(attained);
        errno_t errres = localtime_s(&lt, &timet);
        if(errres != EINVAL){
            size_t result = _strftime_l(tInfo.timeGotten, 32, "%D", &lt, NULL);
            if(result == 0){
                printf("ERROR, COULDN'T GET TIME!\n");
                sprintf_s(tInfo.timeGotten, 32, "UNKNOWN");
            }
        } else {
            printf("ERROR, COULDN'T GET LOCALTIME!\n");
            sprintf_s(tInfo.timeGotten, 32, "UNKNOWN");
        }
        printf("%s\n", yyjson_get_str(main));
        strcpy_s(tInfo.tierName, 90, yyjson_get_str(main));
        tInfo.tier = yyjson_get_int(curTier);
        tInfo.HorL = yyjson_get_int(horl);
        tInfo.peakTier = yyjson_get_int(peak_tier);
        tInfo.peakHorL = yyjson_get_int(peakhorl);
        tInfo.isRetired = yyjson_get_bool(isRetired);
        AddTier(tInfo);
    }
    CalculatePlayerPoints(sWhere);
    yyjson_doc_free(jsonDoc);
    free((void*)body);
    ChangeState(RESULT_STATE);
    return 0;
}






VOID BeginSearch(UINT8 where){
    sWhere = where;
    ChangeState(LOADING_STATE);
    SHCreateThread(SearchThreadEntry, NULL, 0, NULL);
}