#include "initialconfig.h"
#include "extern/inih/ini.h"
#include <stdlib.h>
#include <processthreadsapi.h>




static INT InitConfigHandler(void* user, const char* section, const char* name, const char* value){
    InitConfig* config = (InitConfig*)user;
    #define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0
    if(MATCH("init", "targetfps")){
        config->targetfps = atoi(value);
        if(config->targetfps == 0){
            config->targetfps = 60;
        }
    }
    if(MATCH("init", "style")){
        config->style = _strdup(value);
        
    }
    return 0;
}

// CAN END PROCESS
InitConfig HandleConfiguration(){
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
        ExitProcess(1);
    }
    return config;
}