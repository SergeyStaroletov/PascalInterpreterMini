//---------------------------------------------------------------------------

#include "semantic.h"
#include "defs.h"

Tree *root;

Tree *mynode;

FILE *ff;
void semPrint(char *data, char *lex) {
  char *s = new char[200];
  char *s1 = new char[200];

  strcpy(s, data);
  strcat(s, " � ������ %d !");
  // CharToOem(s, s1);
  printf(s, lex, pos);
  fflush(stdout);
  delete[] s;
  delete[] s1;
  // getch() ;
  exit(1);
};

void SetLeft(NodeData new_data)
//������� ������ ������� �� ������� �������
{
  Tree *a;
  a = mynode;
  if (mynode == NULL) {
    mynode = new Tree;
    root = mynode;
  } else {
    mynode->lp = new Tree;
    mynode = mynode->lp;
  };
  mynode->lp = NULL;
  mynode->rp = NULL;
  mynode->p = a;
  memcpy(&mynode->data, &new_data, sizeof(NodeData));
  return;
};

void SetRight(NodeData new_data) {
  Tree *a;
  a = mynode;
  if (mynode == NULL) {
    mynode = new Tree;
    root = mynode;
  } else {
    mynode->rp = new Tree;
    mynode = mynode->rp;
  };
  mynode->lp = NULL;
  mynode->rp = NULL;
  mynode->p = a;
  memcpy(&mynode->data, &new_data, sizeof(NodeData));
  return;
};

NodeData *FindUpFun(Tlex l)
//����� ������������� � ������� , �������� ����� � �������������� �� ������
//�������
{
  Tree *tmp, *tp;

  tmp = mynode;
  while (tmp != NULL) {
    if (!strcmp(tmp->data.id, l)) {
      //�����
      return &tmp->data;
      // break ;
    };
    tp = tmp;
    tmp = tmp->p;
    if (tmp != NULL)
      if (tmp->rp != NULL)
        if (tp == tmp->rp) {
          if (!strcmp(tmp->data.id, l)) return &tmp->data;
          break;
        };

  };  // wh
  return NULL;
};

NodeData *FindUp(Tlex l)
//����� ������������� � ������� , �������� �����
{
  Tree *tmp;
  tmp = mynode;
  while (tmp != NULL) {
    if (!strcmp(tmp->data.id, l)) {
      //�����
      return &tmp->data;
      // break ;
    };
    tmp = tmp->p;
  };  // wh
  return NULL;
};

int a() {
  NodeData new_data;
  Tlex l;
  strcpy(l, "my_id");
  new_data.t = typeVar;
  new_data.dataType = typeInt;
  strcpy(new_data.id, l);

  SetLeft(new_data);
  SetLeft(new_data);

  strcpy(l, "ol_id");
  strcpy(new_data.id, l);
  SetLeft(new_data);

  NodeData *myd;

  myd = FindUp("myid");

  // int c=2+3 ;
};

Tree *Sem13() { return mynode; }

//������� � ������� ��� ����
void Sem14AddIdWithoutAType(Tlex name) {
  NodeData new_data;
  //���������

  NodeData *myd = FindUpFun(name);

  if (myd != NULL) {
    //��� ���� !
    semPrint("��������� ������������� '%s'", name);
  };
  new_data.t = typeVar;
  new_data.dataType = typeNone;
  strcpy(new_data.id, name);
  SetLeft(new_data);
};

//���������� ������������� ��� �� ������������
int SemReturnSemTypeByLexType(int t) {
  if (t == Tint) return typeInt;
  if (t == Tbool) return typeBool;
  return typeNone;
};

//�������� ��� typenone �� ������ ���, ���������� ����� �� ������
void Sem15ChangeToType(Tree *n, int tt) {
  //   |(n)
  // |
  Tree *tmp = mynode;

  while (tmp != n) {
    tmp->data.dataType = tt;
    //�������� ������
    tmp->data.value = new int;
    //� ��������� ��������
    *tmp->data.value = 0;
    tmp = tmp->p;
  };
};

//������� � ������� ��������� ��� ����
void Sem14InsertConstant(Tlex name) {
  NodeData new_data;
  //���������
  // data *myd = FindUp(name) ;
  NodeData *myd = FindUpFun(name);
  if (myd != NULL) {
    //��� ���� !
    semPrint("��������� ������������� '%s'", name);
  };
  new_data.t = typeConst;
  new_data.dataType = typeNone;
  strcpy(new_data.id, name);
  SetLeft(new_data);
};

void Sem15c(Tlex l, bool flag_minus) {
  int z;
  int tip;
  //�������� � ��� � ��������
  // tree *tmp=mynode ;

  if (l[0] == 'T' || l[0] == 't') {  // bool value
    z = 1;
    tip = typeBool;
  } else if (l[0] == 'F' || l[0] == 'f') {
    z = 0;
    tip = typeBool;
  } else {
    //�������� �������������
    char s[40];
    strcpy(s, "0000000000000000000");
    int ofs = 19 - strlen(l);
    for (int j = 0; j < strlen(l); j++) {
      s[ofs + j] = l[j];
    };
    if (strcmp(s, "0000000002147483647") > 0) {
      semPrint("������� ������� �������� ��������� - %s", l);
      tip = typeNone;
    };
    z = atoi(l);

    if (flag_minus) z = -z;
    tip = typeInt;
  };
  //������ �������
  mynode->data.dataType = tip;
  mynode->data.znach = z;
  mynode->data.value = &(mynode->data.znach);
};

//������
Tree *Sem16AddChildFunction(Tlex l) {
  //������� ������� - �������
  Tree *u;
  NodeData new_data;
  //���������

  NodeData *myd = FindUpFun(l);

  if (myd != NULL) {
    //��� ���� !
    semPrint("��������� ������������� '%s'", l);
  };
  new_data.t = typeFunc;
  new_data.dataType = typeNone;
  new_data.param = 0;
  strcpy(new_data.id, l);
  SetLeft(new_data);
  u = mynode;
  //�������
  //������� ������� ������� �������
  new_data.t = typeNone;
  new_data.dataType = typeNone;
  strcpy(new_data.id, "");
  SetRight(new_data);
  return u;
};

//�������� ����� ���������� � �������
void Sem17ChangeNParamFun(Tree *k) { k->data.param++; };

//�������� �������� � �������
void Sem14AddParamFun(Tlex name, bool fr, bool var) {
  NodeData new_data;
  //���������

  NodeData *myd = FindUpFun(name);

  if (myd != NULL) {
    //��� ���� !
    semPrint("��������� ������������� '%s'", name);
  };

  new_data.t = typeParam;
  new_data.dataType = typeNone;
  if (var)
    new_data.type_param = parameterVar;
  else
    new_data.type_param = parameter;

  strcpy(new_data.id, name);

  if (fr == true) {  //������ ����� - �������� ������
    memcpy(&mynode->data, &new_data, sizeof(NodeData));
  } else  //����� - �����
    SetLeft(new_data);
};

//�������� �������. ��� �������
void Sem15ChangeUndefinedTypeFun(Tree *n, int tt) {
  n->data.dataType = tt;
  n->data.value = new int;
  *(n->data.value) = 0;
};

void Sem18(Tree *k) { mynode = k; };

int Sem1CheckVar(Tlex l, bool *var, int *znach, int *&address) {
  NodeData *myd = FindUp(l);
  if (myd == NULL)  //�� ������
  {
    semPrint("������������� %s �� ������, ", l);
    return typeNone;
  };
  if (myd->t == typeFunc) semPrint("�������� ������������� '%s'", l);
  if (myd->t == typeVar || myd->t == typeParam)
    *var = true;
  else
    *var = false;

  //�������� ����������
  *znach = *myd->value;
  address = myd->value;

  return myd->dataType;
};

int Sem2CheckNumber(Tlex l, int *znach) {
  // 2147483647
  if (!isdigit(l[0])) {
    // true/false
    if (l[0] == 't') *znach = 1;
    if (l[0] == 'f') *znach = 0;

    return typeBool;
  };
  char s[40];
  strcpy(s, "0000000000000000000");
  int ofs = 19 - strlen(l);
  for (int j = 0; j < strlen(l); j++) {
    s[ofs + j] = l[j];
  };
  if (strcmp(s, "0000000002147483647") > 0) {
    semPrint("������� ������� �������� ��������� - %s", l);
    *znach = 0;
    return typeNone;
  };

  *znach = atoi(l);

  /*
  AnsiString sl = "";
  try {
    sl.sprintf("%s", l);
    fflush(stdout);
    *znach = StrToInt(sl);
  } catch (Exception &e) {
    printf("\nShutdown with runtime error:");
    e.Message[1] = ' ';
    printf("%s.", e.Message.c_str());
    fflush(stdout);
    *znach = 0;
  };
  */

  return typeInt;
};

//��������� �� �������
int Sem5CheckToFun(Tlex l, Tree **n) {
  NodeData *myd = FindUp(l);
  if (myd == NULL)  //�� ������
  {
    semPrint("������������� '%s' �� ������, ", l);
    return typeNone;
  };

  if (myd->t != typeFunc) {
    semPrint("������������� '%s' �� �������� ������ �������, ", l);
    return typeNone;
  };

  Tree *tmp;
  *n = NULL;

  //����� n

  tmp = mynode;
  while (tmp != NULL) {
    if (!strcmp(tmp->data.id, l)) {
      //�����
      *n = tmp;
      break;
    };
    tmp = tmp->p;
  };  // wh

  return myd->dataType;
};

//��������� ��� ��������� � ������� k � ������� * n �� ��� t
void Sem6CheckKthParamFunc(int t, Tree *n, int k, bool var) {
  int j;
  Tree *tmp = n;
  if (k > tmp->data.param)
    semPrint("��������� ����� ���������� � ������� '%s'", tmp->data.id);

  tmp = tmp->rp;  //������ ��������
  for (j = 2; j <= k; j++) tmp = tmp->lp;

  //��������� ���
  if (t != tmp->data.dataType)
    semPrint("�������� ��� ��������� '%s'", tmp->data.id);

  if (tmp->data.type_param == parameterVar)
    if (!var)
      semPrint("�������� var '%s' �� ����� ���� ����������", tmp->data.id);
};

void Sem7CheckFunParamCount(Tree *n, int k) {
  if (n->data.param != k)
    semPrint("�� ������� ���������� � ������� '%s'", n->data.id);
};

int Sem71ReturnType(Tree *n) { return n->data.dataType; };

int Sem3CheckTwoTypesApplicable(int t1, int t2, int oper) {
  switch (oper) {
    case Tplus:
    case Tminus:
    case Tmod:
    case Tdiv:
    case Tmult: {
      if (t1 == typeInt && t2 == typeInt) return typeInt;
      if (t1 == typeNone && t2 == typeNone) return typeNone;
      if (t1 == typeNone && t2 == typeInt) return typeNone;
      if (t1 == typeInt && t2 == typeNone) return typeNone;
      semPrint("������������ �����%s", "");
      return typeNone;
      break;
    };
    case Tand:
    case Tor:
    case Txor: {
      if (t1 == typeInt && t2 == typeInt) return typeInt;
      if (t1 == typeBool && t2 == typeBool) return typeBool;
      if (t1 == typeNone && t2 == typeNone) return typeNone;
      if (t1 == typeInt && t2 == typeNone) return typeNone;
      if (t1 == typeNone && t2 == typeInt) return typeNone;
      if (t1 == typeBool && t2 == typeNone) return typeNone;
      if (t1 == typeNone && t2 == typeBool) return typeNone;
      semPrint("������������ �����%s", "");
      return typeNone;
    };
    case Tbolee:
    case Tmenee:
    case Tbolequ:
    case Tmenequ:
    case Tequ:
    case Tnonequ: {
      if (t1 == typeInt && t2 == typeInt) return typeBool;
      if (t1 == typeBool && t2 == typeBool) return typeBool;
      if (t1 == typeNone && t2 == typeNone) return typeNone;
      if (t1 == typeInt && t2 == typeNone) return typeNone;
      if (t1 == typeNone && t2 == typeInt) return typeNone;
      if (t1 == typeBool && t2 == typeNone) return typeNone;
      if (t1 == typeNone && t2 == typeBool) return typeNone;
      semPrint("������������ �����%s", "");
    }
  }
}

int Sem31CheckTypeUnary(int t1, int oper) {
  if (oper == Tplus || oper == Tminus) {
    if (t1 == typeInt) return typeInt;
    if (t1 == typeNone) return typeNone;
    semPrint("������������ ����� � ������� ��������%s", "");
    return typeNone;
  }

  if (oper == Tnot) {
    if (t1 == typeInt) return typeInt;
    if (t1 == typeBool) return typeBool;
    if (t1 == typeNone) return typeBool;
    semPrint("������������ ����� � ������� ��������%s", "");
    return typeNone;  //������� �� ���.
  }
  return t1;
};

//***************************************************
void _printtree(Tree *t) {
  if (t) {
    fprintf(ff, "%d %s ", t, t->data.id);
    if (t->data.t == typeConst)
      fprintf(ff, "c %d %d", t->data.znach, t->data.dataType);
    if (t->data.t == typeVar) fprintf(ff, "v %d 0", t->data.dataType);
    if (t->data.t == typeFunc)
      fprintf(ff, "f %d %d", t->data.param, t->data.dataType);
    if (t->data.t == typeParam)
      fprintf(ff, "p %d %d", t->data.type_param, t->data.dataType);
    fprintf(ff, " %d %d %d\n", t->p, t->lp, t->rp);
    if (t->lp) _printtree(t->lp);
    if (t->rp) _printtree(t->rp);
  };
};

int Sem9CheckIdAndReturnType(Tlex l) {
  NodeData *myd = FindUp(l);
  if (myd == NULL)  //�� ������
  {
    semPrint("������������� '%s' �� ������, ", l);
    return typeNone;
  };

  if (myd->t != typeVar && myd->t != typeFunc && myd->t != typeParam) {
    semPrint("������������� '%s' �� �������� ������ ����������", l);
    return typeNone;
  };
  //����� �������

  if (myd->t == typeFunc) {
    Tree *tmp, *tp;

    tmp = mynode;
    while (tmp != NULL) {
      tp = tmp;
      tmp = tmp->p;
      if (tmp != NULL)
        if (tmp->rp != NULL)
          if (tp == tmp->rp) {
            if (!strcmp(tmp->data.id, l)) {
              //�����
              // return &tmp->data ;
              break;
            } else {
              semPrint("�������� �������� �������� �������� '%s'", l);
              break;
            };
          };
    };
  };
  return myd->dataType;
};

void Sem91CheckAssignmentTypes(int T1, int T2) {
  if (T1 != T2) semPrint("���� ������ ��� ������������ ������ ���������%s", "");
};

void Sem8CheckTypeWhile(int t) {
  if (t != typeBool) semPrint("��� while ����� ��������� ���� boolean%s", "");
};

void printTree() {
  ff = fopen("tree.tree", "w");
  _printtree(root);
  fclose(ff);
};

void setNode(Tree *node) { mynode = node; };
Tree *getNode() { return mynode; };

//---------------------------------------------------------------------------
