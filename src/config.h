#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED








#define _AMD64_
#include <minwindef.h>






typedef struct Config {
    UINT targetfps;
    CHAR style[255];
} Config;




Config HandleConfig();








#endif