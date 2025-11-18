#ifndef OSABS_H_INCLUDED
#define OSABS_H_INCLUDED





#include <stdlib.h>
#include <string.h>



#ifdef _WIN32
#include <Windows.h>
#define safe_sprintf sprintf_s
#define safe_strcpy strcpy_s
#elif 
#include <unistd.h>
#define safe_sprintf snprintf
#define safe_strcpy strncpy
#endif












#endif