#include "osabs.h"




#ifdef _WIN32
#define safe_sprintf sprintf_s
#elif 
#define safe_sprintf snprintf
#endif
