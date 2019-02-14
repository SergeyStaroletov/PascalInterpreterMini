#ifndef semanticH
#define semanticH

#include "defs.h"

extern int currentPos;

struct NodeData {
  Tobj t;        //���
  Tlex id;       //�������������
  int pos;       //������� � �������� ������
  int dataType;  //��� ��� ��� �����. ��������
  int *value;  //����� � ������� - ��������� �� ��������

  union {
    int znach;       //�������� ��� const
    int param;       //����� ����� ��� func
    int type_param;  //�������� ������� - ��� ���(�� ������, ��������)
  };
};

//� ������
struct Tree {
  NodeData data;
  Tree *p;
  Tree *lp;
  Tree *rp;
};

NodeData *FindUp(Tlex l);
//��������� ��������
Tree *Sem13();
void Sem14AddIdWithoutAType(Tlex name);
void Sem14InsertConstant(Tlex name);
void Sem14AddParamFun(Tlex name, bool fr, bool var);
int SemReturnSemTypeByLexType(int t);
void Sem15ChangeToType(Tree *n, int tt);
void Sem15c(Tlex l, bool flag_minus);
Tree *Sem16AddChildFunction(Tlex l);
void Sem17ChangeNParamFun(Tree *k);
void Sem15ChangeUndefinedTypeFun(Tree *n, int tt);
void Sem18(Tree *k);
//��������� �������
int Sem1CheckVar(Tlex l, bool *var, int *znach, int *&address);
int Sem2CheckNumber(Tlex l, int *znach);

int Sem5CheckToFun(Tlex l, Tree **n);

void Sem6CheckKthParamFunc(int t, Tree *n, int k, bool var);
void Sem7CheckFunParamCount(Tree *n, int k);
int Sem71ReturnType(Tree *n);
void Sem8CheckTypeWhile(int t);
int Sem9CheckIdAndReturnType(Tlex l);
void Sem91CheckAssignmentTypes(int T1, int T2);

int Sem3CheckTwoTypesApplicable(int t1, int t2, int oper);
int Sem31CheckTypeUnary(int t1, int oper);

void setNode(Tree *node);
Tree *getNode();

void printTree();
//---------------------------------------------------------------------------
#endif
