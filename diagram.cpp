#include "defs.h"

#include "diagram.h"
#include "interpret.h"
#include "scaner.h"
#include "semantic.h"

int currentPos = 0;
char isInterpretation;

//---------------------------------------------------------------------------

void syntax() {
  currentPos = 1;
  isInterpretation = 1;
  stackInit(32768);
  S();
}

//---------------------------------------------------------------------------

void printBug(char *data, char *lex) {
  char *s = new char[200];

  if (!strcmp(lex, "")) {
    strcpy(s, "Ошибка ! Ожидалось : '");
    strcat(s, data);
    strcat(s, "' в строке ");
  } else {
    strcpy(s, "Ошибка ! Ожидалось : '");
    strcat(s, data);
    strcat(s, "', найдено : '");
    strcat(s, lex);
    strcat(s, "' в строке ");
  }

  printf("%s %d\n", s, currentPos);
  fflush(stdout);

  delete[] s;

  exit(1);
}

//---------------------------------------------------------------------------

int readln() {
  int ret = 0;
  Tlex l;
  int t;
  t = scanerNextToken(l);
  if (t != Tzs) printBug("закрывающая скобка оператора readln()", l);

  if (isInterpretation) {
    fflush(stdin);
    scanf("%d", &ret);
  }
  return ret;
}

//---------------------------------------------------------------------------

int write(bool ln) {
  int t;
  Tlex l;
  Tlex l1;
  char vs[255];
  bool one = true;  //только один оператор - переменная
  bool isOneVar = false;
  strcpy(vs, "");

  t = scanerNextToken(l);
  strcpy(l1, l);
  one = true;
  while (t != Tzs) {
    if (strcmp(l1, "'")) {
      strcat(vs, l1);
      strcat(vs, " ");
    }
    t = scanerNextToken(l1);
    if (one && !strcmp(l1, ")")) isOneVar = true;
    one = false;
  }

  if (isInterpretation) {
    if (isOneVar) {  //выводимый оператор-одна переменная
      //найти её значение в дереве
      int zn;
      bool aaa;
      int *a;
      int T = Sem1CheckVar(l, &aaa, &zn, a);
      if (T == typeInt) printf("%d", zn);
      if (T == typeBool)
        if (zn == 0)
          printf("false");
        else
          printf("true");

    } else {
      printf("%s", vs);
    }
    if (ln) printf("\n");
    fflush(stdout);
  }
  return 0;
}

//---------------------------------------------------------------------------

void S() {
  O();
  N();

  int t;
  Tlex l;

  t = scanerNextToken(l);
  if (t != Tpoint) printBug(".", l);
  t = scanerNextToken(l);
  if (t != Teof) printf("Warning: text after '.' !\n");
  fflush(stdout);
}

//---------------------------------------------------------------------------

void O() {
  char localInterpretation = isInterpretation;
  isInterpretation = 0;
  Tlex l;
  int t;
  int uk1;
  uk1 = getLinePtr();
  t = scanerNextToken(l);
  putLinePtr(uk1);

  while (t == Tvar || t == Tconst || t == Tfun) {
    A();
    uk1 = getLinePtr();
    t = scanerNextToken(l);
    putLinePtr(uk1);
  }
  isInterpretation = localInterpretation;
}

//---------------------------------------------------------------------------

void A() {
  Tlex l;
  int t;
  Tree *k;
  t = scanerNextToken(l);
  bool fr = true;

  if (t == Tvar)
    B();
  else if (t == Tconst)
    G();
  else
      //функция
      if (t == Tfun) {
    t = scanerNextToken(l);
    if (t != Tid) printBug("идентификатор", l);
    //занести функцию с пустым типом
    k = Sem16AddChildFunction(l);

    t = scanerNextToken(l);
    if (t != Tos) printBug("(", l);
    // K

    Tlex lk;
    int tk;
    int uk1k;

    do {
      uk1k = getLinePtr();
      tk = scanerNextToken(lk);
      bool is_var = false;
      if (tk == Tvar)
        is_var = true;
      else if (tk == Tid) {
        putLinePtr(uk1k);
      } else
        printBug("идентификатор|var", lk);

      Tree *n = Sem13();

      Tlex l1k;
      int t1k;
      int uk11k;

      do {
        t1k = scanerNextToken(l1k);
        if (t1k != Tid) printBug("идентефикатор", l1k);
        //добавить пустой id
        Sem14AddParamFun(l1k, fr, is_var);
        if (fr) n = n->p;
        fr = false;
        Sem17ChangeNParamFun(k);  //увеличили число параметров
        uk11k = getLinePtr();
        t1k = scanerNextToken(l1k);
      } while (t1k == Tpause);
      putLinePtr(uk11k);
      tk = scanerNextToken(lk);
      if (tk != Tdv) printBug(":", lk);
      tk = scanerNextToken(lk);
      if (tk != Tint && tk != Tbool) printBug("integer|boolean", lk);
      int tt = SemReturnSemTypeByLexType(tk);
      Sem15ChangeToType(n, tt);

      uk1k = getLinePtr();
      tk = scanerNextToken(lk);
    } while (tk == Ttz);
    putLinePtr(uk1k);
    //

    t = scanerNextToken(l);
    if (t != Tzs) printBug(")", l);
    t = scanerNextToken(l);
    if (t != Tdv) printBug(":", l);
    t = scanerNextToken(l);
    if (t != Tint && t != Tbool) printBug("имя типа", l);
    //завершить
    int tt = SemReturnSemTypeByLexType(t);
    Sem15ChangeUndefinedTypeFun(k, tt);

    t = scanerNextToken(l);
    if (t != Ttz) printBug(";", l);
    O();
    IntSaveFuncPosition(getLinePtr(), k);
    N();
    Sem18(k);
    t = scanerNextToken(l);
    if (t != Ttz) printBug(";", l);
  } else
    printBug("var|const|function", l);
}

//---------------------------------------------------------------------------

//описания переменных
void B() {
  Tlex l;
  int t;
  Tree *n;  //указатель на последний перед занесением элемент данных
  do {
    n = Sem13();
    // L() ;
    Tlex l1;
    int t1;
    int uk1;
    do {
      t1 = scanerNextToken(l1);
      if (t1 != Tid) printBug("идентефикатор", l1);
      Sem14AddIdWithoutAType(l1);  //занести в таблицу без указания типа
      uk1 = getLinePtr();
      t1 = scanerNextToken(l1);
    } while (t1 == Tpause);
    putLinePtr(uk1);

    t = scanerNextToken(l);
    if (t != Tdv) printBug(":", l);
    t = scanerNextToken(l);
    if (t != Tint && t != Tbool) printBug("integer|boolean", l);
    int tt = SemReturnSemTypeByLexType(t);
    Sem15ChangeToType(n, tt);

    t = scanerNextToken(l);
    if (t != Ttz) printBug(";", l);

    uk1 = getLinePtr();
    t = scanerNextToken(l);
    putLinePtr(uk1);

  } while (t == Tid);
}

//---------------------------------------------------------------------------

void L() {
  //было, теперь нет
}

//---------------------------------------------------------------------------

void K() {}

//константы
void G() {
  Tlex l;
  int t;
  int uk1;

  bool isMinus = false;
  do {
    // L() ;

    t = scanerNextToken(l);
    if (t != Tid) printBug("идентефикатор константы", l);
    //занести
    Sem14InsertConstant(l);
    t = scanerNextToken(l);
    if (t != Tequ) printBug("=", l);
    t = scanerNextToken(l);
    if (t != Tplus && t != Tminus && t != Ttrue && t != Tfalse && t != Tnumber)
      printBug("значение integer или boolean", l);
    if (t == Tplus || t == Tminus) {
      if (t == Tminus) isMinus = true;
      t = scanerNextToken(l);
      if (t != Tnumber) printBug("значение integer", l);
    }

    //занести
    Sem15c(l, isMinus);

    t = scanerNextToken(l);
    if (t != Ttz) printBug(";", l);

    uk1 = getLinePtr();
    t = scanerNextToken(l);
    putLinePtr(uk1);
  } while (t == Tid);
}

//---------------------------------------------------------------------------

void N() {
  Tlex l;
  int t;
  int uk1;

  t = scanerNextToken(l);

  if (t != Tbegin) printBug("begin", l);

  do {
    C();
    uk1 = getLinePtr();
    t = scanerNextToken(l);
  } while (t == Ttz);
  putLinePtr(uk1);
  t = scanerNextToken(l);
  if (t != Tend) printBug("end", l);
}


//---------------------------------------------------------------------------

void C() {
  Tlex l;
  Tlex lex;
  int z;
  int t;

  int uk1 = getLinePtr();
  t = scanerNextToken(l);

  if (t == Tbegin) {
    putLinePtr(uk1);
    N();
  } else if (t == Tid) {
    strcpy(lex, l);
    int T1, T2;
    T1 = Sem9CheckIdAndReturnType(l);
    t = scanerNextToken(l);
    if (t != Tassign) printBug(":=", l);
    int *addr;
    I(&T2, &z, addr);
    Sem91CheckAssignmentTypes(T1, T2);
    if (isInterpretation) IntAssignValueOrAddrToVar(T1, T2, lex, &z, addr);

  } else if (t == Twhile) {
    putLinePtr(uk1);
    W();
  } else
    putLinePtr(uk1);
}

//---------------------------------------------------------------------------

void W() {
  int z;
  Tlex l;
  int t, uk1;
  int T;
  int localInterpretation;
  t = scanerNextToken(l);
  if (t != Twhile) printBug("while", l);

  uk1 = getLinePtr();
  localInterpretation = isInterpretation;
  int *addr;
while_iter:
  I(&T, &z, addr);

  Sem8CheckTypeWhile(T);
  t = scanerNextToken(l);
  if (t != Tdo) printBug("do", l);

  if (isInterpretation && z)
    isInterpretation = 1;
  else
    isInterpretation = 0;
  C();

  if (isInterpretation) {
    putLinePtr(uk1);
    goto while_iter;
  }

  isInterpretation = localInterpretation;
}

//---------------------------------------------------------------------------

bool I(int *i, int *znach, int *&address) {
  bool ret = false;
  Tlex l;
  int t;
  int uk1;
  uk1 = getLinePtr();
  t = scanerNextToken(l);

  int T1, T2, To;
  int z1 = 0, z2 = 0;
  bool flag_plus = false;

  if (t != Tplus && t != Tminus)
    putLinePtr(uk1);
  else
    flag_plus = true;

  ret = A1(&T1, &z1, address);
  if (flag_plus) T1 = Sem31CheckTypeUnary(T1, t);
  if (t == Tminus) z1 *= -1;

  uk1 = getLinePtr();
  t = scanerNextToken(l);
  while (t == Tbolee || t == Tbolequ || t == Tmenee || t == Tmenequ ||
         t == Tequ || t == Tnonequ) {
    ret = false;
    A1(&T2, &z2, address);
    To = T1;

    T1 = Sem3CheckTwoTypesApplicable(T1, T2, t);

    if (isInterpretation) z1 = IntCalcOperationResult(To, T2, z1, z2, t);

    uk1 = getLinePtr();
    t = scanerNextToken(l);
  };
  putLinePtr(uk1);

  *i = T1;
  *znach = z1;
  return ret;
}

//---------------------------------------------------------------------------

bool A1(int *i, int *znach, int *&address) {
  bool ret = false;
  Tlex l;
  int t;
  int T1, T2, To;
  int z1 = 0, z2 = 0;
  int uk1;

  ret = A2(&T1, &z1, address);
  uk1 = getLinePtr();
  t = scanerNextToken(l);

  while (t == Tplus || t == Tminus || t == Tor || t == Txor) {
    A2(&T2, &z2, address);
    ret = false;
    To = T1;
    T1 = Sem3CheckTwoTypesApplicable(T1, T2, t);
    if (isInterpretation) z1 = IntCalcOperationResult(To, T2, z1, z2, t);
    uk1 = getLinePtr();
    t = scanerNextToken(l);
  };
  putLinePtr(uk1);

  *i = T1;
  *znach = z1;
  return ret;
}

//---------------------------------------------------------------------------

bool A2(int *i, int *znach, int *&address) {
  bool ret = false;
  Tlex l;
  int t;
  int uk1;
  int T1, T2, To;
  int z1, z2;
  bool flag_not = false;
  uk1 = getLinePtr();
  t = scanerNextToken(l);
  if (t != Tnot)
    putLinePtr(uk1);
  else
    flag_not = true;

  ret = A4(&T1, &z1, address);
  if (flag_not) {
    T1 = Sem31CheckTypeUnary(T1, t);
    ret = false;
  };
  if (flag_not) z1 = !z1;

  uk1 = getLinePtr();
  t = scanerNextToken(l);
  while (t == Tmult || t == Tdiv || t == Tmod || t == Tand) {
    ret = false;
    A4(&T2, &z2, address);
    To = T1;
    T1 = Sem3CheckTwoTypesApplicable(T1, T2, t);
    if (isInterpretation) z1 = IntCalcOperationResult(To, T2, z1, z2, t);
    uk1 = getLinePtr();
    t = scanerNextToken(l);
    if (t != Tnot)
      putLinePtr(uk1);
    else

      T1 = Sem31CheckTypeUnary(T1, t);

    uk1 = getLinePtr();
    t = scanerNextToken(l);
  }
  putLinePtr(uk1);

  *i = T1;
  *znach = z1;
  return ret;
}

//---------------------------------------------------------------------------

bool A4(int *i, int *znach, int *&address) {
  bool ret;
  Tlex l1, l;
  int t;
  int uk1;
  int T;
  address = NULL;

  t = scanerNextToken(l1);

  if (t == Tid) {
    uk1 = getLinePtr();
    t = scanerNextToken(l);
    if (t != Tos) {
      putLinePtr(uk1);
      //идентификатор
      //проверить, переменная ли
      T = Sem1CheckVar(l1, &ret, znach, address);
      *i = T;

      return ret;
    } else {
      //вызов ф-ии
      int ukaz;
      Tree *funNode;  //указатель в дереве на функцию

      int k = 0;  //номер параметра

      if (!strcmp(l1, "readln")) {
        *znach = readln();
        *i = typeInt;
        return false;
      }

      if (!strcmp(l1, "write")) {
        *znach = write(false);
        *i = typeInt;
        return false;
      }

      if (!strcmp(l1, "writeln")) {
        *znach = write(true);
        *i = typeInt;
        return false;
      }

      T = Sem5CheckToFun(l1, &funNode);

      ukaz = IntGetPositionOfFunctionText(
          l1);  //получить указатель на текст функции

      do {
        int T1;
        int *addr;
        bool var = I(&T1, znach, addr);  // T1=1 ;
        k++;
        Sem6CheckKthParamFunc(T1, funNode, k, var);
        if (isInterpretation)
          IntStoreParamToStack(funNode, k, znach, addr);  //помять стек и дерево
        uk1 = getLinePtr();
        t = scanerNextToken(l);
      } while (t == Tpause);
      putLinePtr(uk1);
      t = scanerNextToken(l);
      if (t != Tzs) printBug(")", l);
      Sem7CheckFunParamCount(funNode, k);
      int T1 = Sem71ReturnType(funNode);
      *i = T1;
      // add-on
      if (isInterpretation) {
        int uk2 = getLinePtr();
        putLinePtr(ukaz);
        // create run-time environment
        Tree *t = IntRunFunction(funNode);
        N();  //тело
        putLinePtr(uk2);
        IntPopParamFromStack(funNode, k);        //     param
        *znach = IntGetFunctionReturn(funNode);  // znach func

        printf("\n function call with result = %d\n", *znach);

        Sem18(t);  // vernut'
      }

      return false;
      //зак. вызов ф-ии
    }

    //зак. вызов ф-ии
  } else if (t == Tnumber) {
    T = Sem2CheckNumber(l1, znach);
    *i = T;
    return false;

  } else if (t == Ttrue || t == Tfalse) {
    T = Sem2CheckNumber(l1, znach);
    *i = T;
    return false;

  } else if (t == Tos) {
    ret = I(&T, znach, address);
    t = scanerNextToken(l);
    if (t != Tzs) printBug(")", l);
    *i = T;
    return ret;
  } else
    printBug("выражение|вызов функции", l1);

  *i = typeNone;
  return false;
}
