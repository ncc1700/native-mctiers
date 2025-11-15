#include "search.h"
#include "extern/naett/naett.h"
#include "extern/cjson/cJSON.h"
#include "result.h"
#include "state.h"
#include "states/searchstate.h"
#include <stdio.h>
#include <stdlib.h>
#include <Shlwapi.h>

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
        Sleep(1);
    }
    if(naettGetStatus(res) < 0){
        return FALSE;
    }
    int bodyLength = 0;
    const PCHAR body = (const PCHAR)naettGetBody(res, &bodyLength);
    printf("%s\n", body);
    cJSON *json = cJSON_Parse(body);
    cJSON *id = cJSON_GetObjectItem(json, "id");
    if(id == NULL) return FALSE;
    sprintf_s(uuid, 40, "%s", id->valuestring);
    cJSON_Delete(json);
    free((void*)body);
    return TRUE;
}


static inline BOOL GetPlayerHead(PCHAR username){
    CHAR url[URL_SIZE];
    sprintf_s(url, URL_SIZE, "https://www.mc-heads.net/head/%s", username);
    naettReq* req = naettRequestWithOptions(url, 0, NULL);
    naettRes* res = naettMake(req);
    while(!naettComplete(res)){
        Sleep(1);
    }
    if(naettGetStatus(res) < 0){
        return FALSE;
    }
    int bodyLength = 0;
    void* body = (void*)naettGetBody(res, &bodyLength);
    printf("head image size is %d\n", bodyLength);

    CHAR temppath[100];
    // TODO: in like 10 years use GetTempPath2W when everyone is on 11 or up
    GetTempPathA(100, temppath);
    CHAR path[255];
    sprintf_s(path, 255, "%s\\mctiers", temppath);
    CHAR headpath[255];
    sprintf_s(headpath, 255, "%s\\mctiers\\head.png", temppath);
    wprintf(L"\nHead is going to be stored at %s\n", headpath);
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
        printf("Couldn't contact mojangs server!\n");
        return 1;
    }
    if(GetPlayerHead(ReturnSearchInput()) == FALSE){
        printf("Couldn't Obtain player head\n");
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
        Sleep(1);
    }
    int bodyLength;
    PCHAR body = (PCHAR)naettGetBody(res, &bodyLength);

    cJSON* json = cJSON_Parse(body);
    cJSON* specific = NULL;

    cJSON_ArrayForEach(specific, json){
        TierInfo tInfo = {0};
        cJSON* curtier = cJSON_GetObjectItem(specific, "tier");
        cJSON* horl = cJSON_GetObjectItem(specific, "pos");
        cJSON* peak_tier = cJSON_GetObjectItem(specific, "peak_tier");
        cJSON* peakhorl = cJSON_GetObjectItem(specific, "peak_pos");
        cJSON* isRetired = cJSON_GetObjectItem(specific, "retired");
        printf("%s\n", specific->string);
        strcpy_s(tInfo.tierName, 90, specific->string);
        tInfo.tier = curtier->valueint;
        tInfo.HorL = horl->valueint;
        tInfo.peakTier = peak_tier->valueint;
        tInfo.peakHorL = peakhorl->valueint;
        tInfo.isRetired = isRetired->valueint;
        AddTier(tInfo);
    }
    CalculatePlayerPoints();
    ChangeState(RESULT_STATE);
    return 0;
}






VOID BeginSearch(UINT8 where){
    sWhere = where;
    ChangeState(LOADING_STATE);
    SHCreateThread(SearchThreadEntry, NULL, 0, NULL);
}