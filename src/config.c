#include "config.h"
#include "extern/yyjson/yyjson.h"
#include <corecrt_search.h>
#include <processthreadsapi.h>
#include <Windows.h>



static inline VOID Error(const char* string){
    MessageBoxA(NULL, string, "Native-MCTiers", MB_OK | MB_ICONERROR);
    ExitProcess(1);
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
    sprintf_s(con.style, 255, "resources/styles/%s.rgs", yyjson_get_str(style));
    yyjson_doc_free(doc);
    return con;
}
