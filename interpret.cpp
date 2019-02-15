//---------------------------------------------------------------------------

#include "interpret.h"
#include "semantic.h"
int *stack;
int **stack2;
int sp = -1;
int sp2 = -1;
int d_max;

//---------------------------------------------------------------------------

void stackInit(int max) {
  d_max = max;
  stack = new int[max];
  stack2 = new int *[max];
  sp = -1;
  sp2 = -1;
}

int pop() { return stack[sp--]; }
int *pop2() { return stack2[sp--]; }

bool push(int i) {
  if (sp >= d_max) {
    printf("\nInternal stack overflow!\n");
    exit(1);
  };
  stack[++sp] = i;
  return true;
}

bool push2(int *i) {
  if (sp >= d_max) {
    printf("\nInternal stack overflow!\n");
    exit(1);
  }
  stack2[++sp] = i;
  return true;
}

//---------------------------------------------------------------------------

//занести в структуру позицию тела функции в исх. тексте
void IntSaveFuncPosition(int uk, Tree *n) { n->data.pos = uk; }

//---------------------------------------------------------------------------

int IntGetPositionOfFunctionText(Tlex l)  //получить указатель на текст функции
{
  Tree *n;
  //найти функцию
  Sem5CheckToFun(l, &n);
  int ret = n->data.pos;
  return ret;
}

//---------------------------------------------------------------------------

void IntStoreParamToStack(Tree *n, int k, int *znach,
                          int *&addr)  //поместить парам. в стек
{
  //для первого
  Tree *t = n;
  if (k == 1)
    t = t->rp;
  else {
    t = t->rp;
    for (int i = 1; i < k; i++) t = t->lp;
  };

  if (t->data.type_param == parameterVar) {  //параметр по адресу
    push2(t->data.value);
    t->data.value = addr;
  } else {
    push(*t->data.value);  //параметр по значению
    *t->data.value = *znach;
  }
}

//---------------------------------------------------------------------------

Tree *IntRunFunction(
    Tree *n) {  //обеспечить работу функции (текущую верш. в дереве)
  Tree *tt = n;
  if (tt->rp) {
    tt = tt->rp;
    while (tt->lp != NULL) tt = tt->lp;
  }

  Tree *nn = getNode();
  setNode(tt);
  return nn;
}

//---------------------------------------------------------------------------

void IntPopParamFromStack(Tree *n, int k) {  //извлечь парам. из стека
  int kk = 0;
  Tree *t = n;
  if (k == 1) {
    t = t->rp;
    if (t->data.param == parameterVar)
      pop2();
    else
      *t->data.value = pop();
  } else {
    t = t->rp;
    kk++;
    while (kk < k && t->lp != NULL) {
      t = t->lp;
      kk++;
    };
    while (t != n) {
      if (t->data.param == parameterVar)
        pop2();
      else
        *t->data.value = pop();
      t = t->p;
    }
  }
}

//---------------------------------------------------------------------------

int IntGetFunctionReturn(Tree *n) {  //получить значение функции
  int ret = *(n->data.value);
  return ret;
}

//---------------------------------------------------------------------------

int IntCalcOperationResult(
    int type1, int type2, int value1, int value2,
    int oper) {  // ret = (type1)value1 (oper) (type2)value2 ;
  int ret = 0;

  if (type1 == typeInt && type2 == typeInt) {
    switch (oper) {
      case Tplus:
        ret = value1 + value2;
        break;
      case Tminus:
        ret = value1 - value2;
        break;
      case Tmult:
        ret = value1 * value2;
        break;
      case Tdiv:
        ret = value1 / value2;
        break;
      case Tequ:
        ret = (value1 == value2);
        break;
      case Tor:
        ret = (value1 | value2);
        break;
      case Tand:
        ret = (value1 & value2);
        break;
      case Txor:
        ret = (value1 ^ value2);
        break;
      case Tbolee:
        ret = (value1 > value2);
        break;
      case Tmenee:
        ret = (value1 < value2);
        break;
      case Tbolequ:
        ret = (value1 >= value2);
        break;
      case Tmenequ:
        ret = (value1 <= value2);
        break;
      case Tnonequ:
        ret = (value1 != value2);
        break;
    }
  }

  if (type1 == typeBool && type2 == typeBool) {
    switch (oper) {
      case Tequ:
        ret = (value1 == value2);
        break;
      case Tor:
        ret = (value1 || value2);
        break;
      case Tand:
        ret = (value1 && value2);
        break;
      case Txor:
        ret = (!(value1 && value2 || !value1 && !value2));
        break;
      case Tbolee:
        ret = (value1 > value2);
        break;
      case Tmenee:
        ret = (value1 < value2);
        break;
      case Tbolequ:
        ret = (value1 >= value2);
        break;
      case Tmenequ:
        ret = (value1 <= value2);
        break;
      case Tnonequ:
        ret = (value1 != value2);
        break;
    }
  }
  return ret;
}

//---------------------------------------------------------------------------

void IntAssignValueOrAddrToVar(int T1, int T2, Tlex lex, int *z,
                               int *&addr) {  //присвоить перем. значение

  if (!isInterpretation) return;
  NodeData *myd = FindUp(lex);

  if (myd->t == typeFunc) {
    Tree *tmp, *tp;

    tmp = getNode();
    while (tmp != NULL) {
      tp = tmp;
      tmp = tmp->p;
      if (tmp != NULL)
        if (tmp->rp != NULL)
          if (tp == tmp->rp) {
            if (!strcmp(tmp->data.id, lex)) {
              *tmp->data.value = *z;
              return;
            } else {
              break;
            }
          }
    }
  }

  if (myd->type_param == parameterVar) {
    // myd->value=addr ;
    *myd->value = *z;
  } else
    *myd->value = *z;
}

//---------------------------------------------------------------------------

#pragma package(smart_init)
