#ifndef semanticH
#define semanticH

#include "defs.h"

extern int currentPos;

struct NodeData {
  Tobj t;        //тип
  Tlex id;       //идентефикатор
  int pos;       //позиция в исходном тексте
  int dataType;  //тип или тип возвр. значения
  int *value;  //адрес в таблице - указатель на значение

  union {
    int znach;       //значение для const
    int param;       //число парам для func
    int type_param;  //параметр функции - его тип(по ссылке, значению)
  };
};

//в дереве
struct Tree {
  NodeData data;
  Tree *p;
  Tree *lp;
  Tree *rp;
};

NodeData *FindUp(Tlex l);
//семантика описаний
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
//семантика вызовов
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
