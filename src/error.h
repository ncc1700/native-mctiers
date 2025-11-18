#ifndef ERROR_H_INCLUDED
#define ERROR_H_INCLUDED




#include "types.h"

#define ERRORLEN 128


VOID ErrCreateErrorWindow(const PCHAR error);
VOID ErrRenderAllErrorWindows();
#endif