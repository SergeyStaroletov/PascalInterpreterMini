#ifndef defscpp
#define defscpp

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXTEXT 10000
#define MAXLEX 20
#define Teof -1
#define Tnone 0
#define Tconst 10
#define Tbegin 11
#define Tend 12
#define Tvar 13
#define Tor 14
#define Tnot 15
#define Txor 16
#define Tfun 18
#define Tand 17
#define Tmod 19
#define Tdiv 20
#define Tint 21
#define Tbool 24
#define Ttrue 22
#define Tfalse 23
#define Twhile 25
#define Tdo 26

#define Tid 30
#define Tnumber 31

#define Tmult 37
#define Tpause 38
#define Tpoint 39
#define Tassign 40
#define Tequ 41
#define Ttz 42
#define Tdv 43
#define Tos 44
#define Tzs 45
#define Tplus 46
#define Tminus 47
#define Tmenee 48
#define Tbolee 49
#define Tbolequ 50
#define Tmenequ 51
#define Tnonequ 52

typedef char Tlex[MAXLEX];
typedef char Ttext[MAXTEXT];
typedef int Tobj;
#define typeVar 99
#define typeParam 88
#define typeFunc 77
#define typeConst 66
#define typeNone -1
#define parameterVar 1
#define parameter 0
#define typeInt 1
#define typeBool 2

#endif
