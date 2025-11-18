#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED








#include "types.h"




typedef struct Config {
    UINT targetfps;
    CHAR style[255];
} Config;




Config HandleConfig();








#endif