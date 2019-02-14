#ifndef _scanerh
#define _scanerh
#include "defs.h"

void putLinePtr(int);
int getLinePtr();
int scanerNextToken(Tlex);
void getData(char *);
extern int pos;

#endif
