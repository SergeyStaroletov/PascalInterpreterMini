//---------------------------------------------------------------------------
#ifndef interpretH
#define interpretH

#include "defs.h"
#include "semantic.h"

extern char isInterpretation;

void stackInit(int max);
int pop();
bool push(int i);

void IntSaveFuncPosition(int uk, Tree *n);  //��������� ������� �������
int IntGetPositionOfFunctionText(Tlex l);  //�������� ��������� �� ����� �������
void IntStoreParamToStack(Tree *n, int k, int *znach,
                          int *&addr);  //��������� �����. � ����
Tree *IntRunFunction(
    Tree *n);  //���������� ������ ������� (������� ����. � ������)
void IntPopParamFromStack(Tree *n, int k);  //������� �����. �� �����
int IntGetFunctionReturn(Tree *n);  //�������� �������� �������

int IntCalcOperationResult(int t1, int t2, int z1, int z2,
                           int oper);  // ret=z1(oper)z2 ;
void IntAssignValueOrAddrToVar(
    int T1, int T2, Tlex lex, int *z,
    int *&addr);  //��������� �����. �������� ��� �����

//---------------------------------------------------------------------------
#endif
