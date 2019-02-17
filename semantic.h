#ifndef semanticH
#define semanticH

#include "defs.h"

extern int currentPos;

struct NodeData {
  Tobj t;        //тип
  Tlex id;       //идентификатор
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
void SemAddIdWithoutAType(Tlex name);
void SemInsertConstant(Tlex name);
void SemAddParamFun(Tlex name, bool fr, bool var);
int SemReturnSemTypeByLexType(int t);
void SemChangeToType(Tree *n, int tt);
void Sem15c(Tlex l, bool flag_minus);
Tree *SemAddChildFunction(Tlex l);
void SemChangeNParamFun(Tree *k);
void SemChangeUndefinedTypeFun(Tree *n, int tt);
void SemSetNodeToGiven(Tree *k);

//семантика вызовов
int SemCheckVar(Tlex l, bool *var, int *znach, int *&address);
int SemCheckNumber(Tlex l, int *znach);
int SemCheckToFun(Tlex l, Tree **n);
void SemCheckKthParamFunc(int t, Tree *n, int k, bool var);
void SemCheckFunParamCount(Tree *n, int k);
int SemReturnType(Tree *n);
void SemCheckTypeWhile(int t);
int SemCheckIdAndReturnType(Tlex l);
void SemCheckAssignmentTypes(int T1, int T2);
int SemCheckTwoTypesApplicable(int t1, int t2, int oper);
int SemCheckTypeUnary(int t1, int oper);

void setNode(Tree *node);
Tree *getNode();

void printTree();
//---------------------------------------------------------------------------
#endif
