#include "extern/naett/naett.h"
#include "extern/raylib/raygui.h"
#include "initialconfig.h"
#include <stdlib.h>
#include "rguiabs.h"
#include "state.h"
#define DEBUG

#ifndef DEBUG
INT WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
#else 
INT main(INT argc, PCHAR argv[])
#endif
{
    // we parse the init.ini config file
    InitConfig config = HandleConfiguration();
    // we set up networking
    naettInit(NULL);

    // we create the window and setup RayGUI
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetTraceLogLevel(LOG_ERROR);
    SetTargetFPS(config.targetfps);
    InitWindow(700, 700, "Native Mctiers");
    RGUIInit(config.style);
    if(config.style != NULL) free(config.style);
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(RGUIGetBackgroundColor());
        RenderCurrentState();
        EndDrawing();
    }
    RGUICleanup();
    CloseWindow();
    
    return 0;
}