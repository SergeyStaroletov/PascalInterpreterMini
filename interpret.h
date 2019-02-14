//---------------------------------------------------------------------------
#ifndef interpretH
#define interpretH

#include "defs.h"
#include "semantic.h"

extern char isInterpretation;

void stackInit(int max);
int pop();
bool push(int i);

void IntSaveFuncPosition(int uk, Tree *n);  //запомнить позицию функции
int IntGetPositionOfFunctionText(Tlex l);  //получить указатель на текст функции
void IntStoreParamToStack(Tree *n, int k, int *znach,
                          int *&addr);  //поместить парам. в стек
Tree *IntRunFunction(
    Tree *n);  //обеспечить работу функции (текущую верш. в дереве)
void IntPopParamFromStack(Tree *n, int k);  //извлечь парам. из стека
int IntGetFunctionReturn(Tree *n);  //получить значение функции

int IntCalcOperationResult(int t1, int t2, int z1, int z2,
                           int oper);  // ret=z1(oper)z2 ;
void IntAssignValueOrAddrToVar(
    int T1, int T2, Tlex lex, int *z,
    int *&addr);  //присвоить перем. значение или адрес

//---------------------------------------------------------------------------
#endif
