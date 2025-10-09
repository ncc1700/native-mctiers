#include "extern/naett/naett.h"
#include "extern/raylib/raylib.h"
#include "extern/inih/ini.h"

#include "rguiabs.h"

#include "state/state.h"
#include <stdlib.h>
#include <minwindef.h>
#include <winbase.h>
#include <string.h>

typedef struct _InitConfig {
    UINT targetfps;
    CHAR* style;
} InitConfig;

static int InitConfigHandler(void* user, const char* section, const char* name, const char* value){
    InitConfig* config = (InitConfig*)user;
    #define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0
    if(MATCH("init", "targetfps")){
        config->targetfps = atoi(value);
        if(config->targetfps == NULL){
            config->targetfps = 60;
        }
    }
    if(MATCH("init", "style")){
        config->style = _strdup(value);
        
    }
    return 0;
}

#define DEBUG

#ifndef DEBUG
INT WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
#else 
INT main(INT argc, PCHAR argv[])
#endif
{
    InitConfig config = {60, NULL};
    if (ini_parse("init.ini", InitConfigHandler, &config) < 0) {
        SetTraceLogLevel(LOG_ERROR);
        SetTargetFPS(30);
        InitWindow(400, 100, "ERROR");
        printf("Can't load init.ini\n");
        while(!WindowShouldClose()){
            BeginDrawing();
            DrawText("Couldn't load configuration file\nplease reinstall native-mctiers", 10, 10, 20, RED);
            ClearBackground(BLACK);
            EndDrawing();
        }
        return 1;
    }
    naettInit(NULL);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetTraceLogLevel(LOG_ERROR);
    printf("%d\n", config.targetfps);
    SetTargetFPS(config.targetfps);
    // what I have to do for res awareness....
    InitWindow(900, 1200, "Initial Window, if you see this please report it");
    int x = GetMonitorWidth(GetCurrentMonitor());
    int y = GetMonitorHeight(GetCurrentMonitor());
    CloseWindow();
    InitWindow(x / 3, y / 1.5, "Native Mctiers");
    RGUIInit(config.style);
    if(config.style != NULL) free(config.style);
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(RGUIGetBackgroundColor());
        RenderStates();
        EndDrawing();
    }
    RGUICleanup();
    CloseWindow();

    return 0;
}