#include "scaner.h"
#include "defs.h"

int uk = 0;
int save_pos = 0;

Ttext t;
int getLinePtr(void) {
  save_pos = pos;
  return uk;
}
void putLinePtr(int p) {
  uk = p;
  pos = save_pos;
  return;
}

void getData(char *name) {
  for (int j = 0; j < MAXTEXT; j++) t[j] = 0;
  // strcpy(t,"") ;
  FILE *f = fopen(name, "rb");
  if (!f) {
    printf("Error: %s not a falid file.", name);
    fflush(stdout);
    exit(1);
  };
  fread(t, sizeof(char), MAXTEXT - 2, f);

  // fgets(t,MAXTEXT,f) ;
  fclose(f);
};

void printerror(char *lex){
    // printf("[error!] in %s\n",lex);
};

void printCommentError(int i) {
  printf("Non ending comment! in line %d\n", pos);
  fflush(stdout);
  exit(1);
};

//\/\/\/\\/\/\/\/\/\\/\/\/\/\/\\/\/\/\/\/\/\/\/\\/\/\/\/\\/\/\\/\\/\/\/\/\\/\/\/\/\/

int scanerNextToken(Tlex l) {
  // 14
  char *sign[] = {"const", "begin",    "end",     "var",   "or",  "not",
                  "xor",   "function", "div",     "mod",   "and", "integer",
                  "true",  "false",    "boolean", "while", "do"};
  int tip[] = {Tconst, Tbegin, Tend, Tvar,  Tor,    Tnot,  Txor,   Tfun, Tdiv,
               Tmod,   Tand,   Tint, Ttrue, Tfalse, Tbool, Twhile, Tdo};

  bool iscomment = false;
  int i = 0;
  // memset(l,0,sizeof(l)) ;
  for (int j = 0; j < MAXLEX; j++) l[j] = 0;

start:
  iscomment = false;
  //������� ���������� ��������
  while (t[uk] == ' ' || t[uk] == '\n' || t[uk] == '\r' || t[uk] == 9) {
    if (t[uk] == '\n') pos++;
    uk++;
    if (t[uk] == '\0') return -1;
  };

  //������� ������������

k0:
  if (t[uk] == '{') {
    uk++;
    goto k1;
  } else if (t[uk] == '(') {
    uk++;
    goto k2;
  } else {
    goto k_fin;
  };
k1:
  if (t[uk] == '\0') {
    printCommentError(uk);
    return -1;
  } else if (t[uk] != '}') {
    if (t[uk] == '\n') pos++;
    uk++;
    goto k1;
  } else {
    uk++;
    iscomment = true;
    goto k_fin;
  };
k2:
  if (t[uk] == '\0') {
    printCommentError(uk);
    return -1;
  } else if (t[uk] == '*') {
    uk++;
    goto k3;
  } else {
    //������ ( , � ����� ��� * - ��� �� ����������
    uk--;
    goto k_fin;
  };
k3:
  if (t[uk] == '\0') {
    printCommentError(uk);
    return -1;
  } else if (t[uk] != '*') {
    if (t[uk] == '\n') pos++;
    uk++;
    goto k3;
  } else {
    uk++;
    goto k4;
  };
k4:
  if (t[uk] == '\0') {
    printCommentError(uk);
    return -1;
  } else if (t[uk] == ')') {
    uk++;
    iscomment = true;
    goto k_fin;
  } else {
    if (t[uk] == '\n') pos++;
    uk++;
    goto k3;
  };
k_fin:
  if (iscomment) goto start;
  //������

  //������� ��� ��� ��  ���������������

id_0:
  if (t[uk] == 0) return -1;
  if (isalpha(t[uk]) || t[uk] == '_') {
    l[i++] = t[uk++];
  id_1:
    if (isalnum(t[uk]) || t[uk] == '_') {
      l[i++] = t[uk++];
      if (i < MAXLEX - 1)
        goto id_1;
      else {
        //������� �������
        // printerror(l) ; return Tnone ;
        while (isalnum(t[uk]) || t[uk] == '_') uk++;

        return Tid;
      };
    } else {
      //��������� �����

      //��������� �� �������� �����
      for (int kl = 0; kl < 17; kl++)
        if (!strcmp(sign[kl], l)) return tip[kl];

      return Tid;
    };
  };
//�����
num_0:
  if ((isalnum(t[uk])) && (!isalpha(t[uk]))) {
    l[i++] = t[uk++];
  num_1:
    if ((isalnum(t[uk])) && (!isalpha(t[uk]))) {
      l[i++] = t[uk++];
      if (i < MAXLEX - 1)
        goto num_1;
      else {  //������� �����
        while ((isalnum(t[uk])) && (!isalpha(t[uk]))) uk++;
        return Tnumber;
      };
    } else {
      //������� �����
      return Tnumber;
    };
  };
  //��������� � ���������
  if (t[uk] == ':') {
    l[i++] = t[uk++];
    if (t[uk] == '=') {
      l[i++] = t[uk++];
      return Tassign;
    } else {
      return Tdv;
    };
  };
  //����� � �������
  if (t[uk] == ';') {
    l[i++] = t[uk++];
    return Ttz;
  };
  //���������
  if (t[uk] == ':') {
    l[i++] = t[uk++];
    return Tdv;
  };
  //  (
  if (t[uk] == '(') {
    l[i++] = t[uk++];
    return Tos;
  };
  //  )
  if (t[uk] == ')') {
    l[i++] = t[uk++];
    return Tzs;
  };
  //+
  if (t[uk] == '+') {
    l[i++] = t[uk++];
    return Tplus;
  };
  //-
  if (t[uk] == '-') {
    l[i++] = t[uk++];
    return Tminus;
  };
  //��������
  if (t[uk] == '*') {
    l[i++] = t[uk++];
    return Tmult;
  };

  //�����
  if (t[uk] == '.') {
    l[i++] = t[uk++];
    return Tpoint;
  };
  //�����
  if (t[uk] == '=') {
    l[i++] = t[uk++];
    return Tequ;
  };

  //�������
  if (t[uk] == ',') {
    l[i++] = t[uk++];
    return Tpause;
  };

  //������ � ������ ��� ����� ��� �������
  if (t[uk] == '<') {
    l[i++] = t[uk++];
    if (t[uk] == '=') {
      l[i++] = t[uk++];
      return Tmenequ;
    } else if (t[uk] == '>') {
      l[i++] = t[uk++];
      return Tnonequ;
    } else

      return Tmenee;
  };
  //������ � ������ ��� �����
  if (t[uk] == '>') {
    l[i++] = t[uk++];
    if (t[uk] == '=') {
      l[i++] = t[uk++];
      return Tbolequ;
    } else
      return Tbolee;
  };
  //����� �����
  if (t[uk] == 0) return -1;
  //�����
  l[i++] = t[uk++];
  printerror(l);
  return 0;
};
