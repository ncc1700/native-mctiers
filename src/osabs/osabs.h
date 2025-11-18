#ifndef OSABS_H_INCLUDED
#define OSABS_H_INCLUDED





#include <stdlib.h>
#include <string.h>



#ifdef _WIN32
#include <Windows.h>
#define safe_sprintf sprintf_s
#elif __linux__
#include <unistd.h>
#define safe_sprintf snprintf
#endif












#endif