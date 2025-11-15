#ifndef INITIALCONFIG_H_INCLUDED
#define INITIALCONFIG_H_INCLUDED







#include "extern/raylib/raylibin.h"




typedef struct _InitConfig {
    UINT targetfps;
    CHAR* style;
} InitConfig;



InitConfig HandleConfiguration();








#endif