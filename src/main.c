#include "config.h"
#include "extern/naett/naett.h"
#include "extern/raylib/raygui.h"
#include "rguiabs.h"
#include "state.h"
#define DEBUG

#ifndef DEBUG
INT WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
#else 
INT main(INT argc, PCHAR argv[])
#endif
{
    // we parse the config.json config file, if fails itll kill the process itself
    Config config = HandleConfig();

    // we set up networking
    naettInit(NULL);

    // we create the window and setup RayGUI
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetTraceLogLevel(LOG_ERROR);
    SetTargetFPS(config.targetfps);
    InitWindow(700, 700, "Native Mctiers");
    RGUIInit(config.style);
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