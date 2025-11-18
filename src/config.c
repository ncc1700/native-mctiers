#include "config.h"
#include "extern/raylib/raylibin.h"
#include "extern/yyjson/yyjson.h"
#include "osabs/osabs.h"



static inline VOID Error(const char* string){
    SetTraceLogLevel(LOG_ERROR);
    SetTargetFPS(30);
    InitWindow(400, 100, "CONFIG ERROR");
    printf("Can't load init.ini\n");
    while(!WindowShouldClose()){
        BeginDrawing();
        DrawText(string, 10, 10, 20, RED);
        ClearBackground(BLACK);
        EndDrawing();
    }
    exit(1);
}



Config HandleConfig(){
    Config con = {0};
    yyjson_read_err err;

    yyjson_doc* doc = yyjson_read_file("config.json", 0, NULL, &err);
    if(doc == NULL){
        Error(err.msg);
    }
    yyjson_val* root = yyjson_doc_get_root(doc);
    if(root == NULL) Error("Couldn't get root");
    yyjson_val* targetfps = yyjson_obj_get(root, "target-fps");
    if(targetfps == NULL) Error("Couldn't get Target FPS");
    yyjson_val* style = yyjson_obj_get(root, "style");
    if(style == NULL) Error("Couldn't get Style");
    con.targetfps = yyjson_get_uint(targetfps);
    printf("%llu - %s\n", yyjson_get_uint(targetfps), yyjson_get_str(style));
    safe_sprintf(con.style, 255, "resources/styles/%s.rgs", yyjson_get_str(style));
    yyjson_doc_free(doc);
    return con;
}
