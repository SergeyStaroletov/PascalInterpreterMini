#ifndef DIAGRAM_H
#define DIAGRAM_H

#include "defs.h"

void syntax();  //корневой
void S();
void A();
void O();
void B();
void L();
void K();
void G();
void N();
void C();
void W();
bool I(int *i, int *result, int *&address);  //выражение
bool A1(int *i, int *result, int *&address);
bool A2(int *i, int *result, int *&address);
bool A4(int *i, int *result, int *&address);

#endif  //  DIAGRAM_H
