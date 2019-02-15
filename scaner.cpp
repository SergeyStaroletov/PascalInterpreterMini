#include "scaner.h"
#include "defs.h"

int posPointer = 0;
int savePos = 0;

Ttext sourceText;

int getLinePtr(void) {
  savePos = currentPos;
  return posPointer;
}

void putLinePtr(int p) {
  posPointer = p;
  currentPos = savePos;
  return;
}

void getData(char *name) {
  for (int j = 0; j < MAXTEXT; j++) sourceText[j] = 0;
  FILE *f = fopen(name, "rb");
  if (!f) {
    printf("Error: %s not a falid file.", name);
    fflush(stdout);
    exit(1);
  }
  fread(sourceText, sizeof(char), MAXTEXT - 2, f);

  fclose(f);
}

void printerror(char *lex) {
  // printf("[error!] in %s\n",lex);
}

void printCommentError(int i) {
  printf("Non ending comment! in line %d\n", currentPos);
  fflush(stdout);
  exit(1);
}

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
  //пропуск незначащих символов
  while (sourceText[posPointer] == ' ' || sourceText[posPointer] == '\n' ||
         sourceText[posPointer] == '\r' || sourceText[posPointer] == 9) {
    if (sourceText[posPointer] == '\n') currentPos++;
    posPointer++;
    if (sourceText[posPointer] == '\0') return -1;
  }

  //пропуск комментариев

k0:
  if (sourceText[posPointer] == '{') {
    posPointer++;
    goto k1;
  } else if (sourceText[posPointer] == '(') {
    posPointer++;
    goto k2;
  } else {
    goto k_fin;
  }
k1:
  if (sourceText[posPointer] == '\0') {
    printCommentError(posPointer);
    return -1;
  } else if (sourceText[posPointer] != '}') {
    if (sourceText[posPointer] == '\n') currentPos++;
    posPointer++;
    goto k1;
  } else {
    posPointer++;
    iscomment = true;
    goto k_fin;
  }
k2:
  if (sourceText[posPointer] == '\0') {
    printCommentError(posPointer);
    return -1;
  } else if (sourceText[posPointer] == '*') {
    posPointer++;
    goto k3;
  } else {
    //символ ( , а потом нет * - это не коментарий
    posPointer--;
    goto k_fin;
  }
k3:
  if (sourceText[posPointer] == '\0') {
    printCommentError(posPointer);
    return -1;
  } else if (sourceText[posPointer] != '*') {
    if (sourceText[posPointer] == '\n') currentPos++;
    posPointer++;
    goto k3;
  } else {
    posPointer++;
    goto k4;
  }
k4:
  if (sourceText[posPointer] == '\0') {
    printCommentError(posPointer);
    return -1;
  } else if (sourceText[posPointer] == ')') {
    posPointer++;
    iscomment = true;
    goto k_fin;
  } else {
    if (sourceText[posPointer] == '\n') currentPos++;
    posPointer++;
    goto k3;
  }
k_fin:
  if (iscomment) goto start;
  //разбор

  //сначала эти как их  идентицфикаторы

id_0:
  if (sourceText[posPointer] == 0) return -1;
  if (isalpha(sourceText[posPointer]) || sourceText[posPointer] == '_') {
    l[i++] = sourceText[posPointer++];
  id_1:
    if (isalnum(sourceText[posPointer]) || sourceText[posPointer] == '_') {
      l[i++] = sourceText[posPointer++];
      if (i < MAXLEX - 1)
        goto id_1;
      else {
        //слишком длинный
        // printerror(l) ; return Tnone ;
        while (isalnum(sourceText[posPointer]) || sourceText[posPointer] == '_')
          posPointer++;

        return Tid;
      }
    } else {
      //закончить идент

      //проверить на ключевое слово
      for (int kl = 0; kl < 17; kl++)
        if (!strcmp(sign[kl], l)) return tip[kl];

      return Tid;
    }
  }
//цифра
num_0:
  if ((isalnum(sourceText[posPointer])) && (!isalpha(sourceText[posPointer]))) {
    l[i++] = sourceText[posPointer++];
  num_1:
    if ((isalnum(sourceText[posPointer])) &&
        (!isalpha(sourceText[posPointer]))) {
      l[i++] = sourceText[posPointer++];
      if (i < MAXLEX - 1)
        goto num_1;
      else {  //длинная цифра
        while ((isalnum(sourceText[posPointer])) &&
               (!isalpha(sourceText[posPointer])))
          posPointer++;
        return Tnumber;
      };
    } else {
      //вернуть цифру
      return Tnumber;
    }
  }
  //присвоить и двоеточие
  if (sourceText[posPointer] == ':') {
    l[i++] = sourceText[posPointer++];
    if (sourceText[posPointer] == '=') {
      l[i++] = sourceText[posPointer++];
      return Tassign;
    } else {
      return Tdv;
    }
  }
  //точка с запятой
  if (sourceText[posPointer] == ';') {
    l[i++] = sourceText[posPointer++];
    return Ttz;
  }
  //двоеточие
  if (sourceText[posPointer] == ':') {
    l[i++] = sourceText[posPointer++];
    return Tdv;
  }
  //  (
  if (sourceText[posPointer] == '(') {
    l[i++] = sourceText[posPointer++];
    return Tos;
  }
  //  )
  if (sourceText[posPointer] == ')') {
    l[i++] = sourceText[posPointer++];
    return Tzs;
  }
  //+
  if (sourceText[posPointer] == '+') {
    l[i++] = sourceText[posPointer++];
    return Tplus;
  }
  //-
  if (sourceText[posPointer] == '-') {
    l[i++] = sourceText[posPointer++];
    return Tminus;
  }
  //умножить
  if (sourceText[posPointer] == '*') {
    l[i++] = sourceText[posPointer++];
    return Tmult;
  }

  //точка
  if (sourceText[posPointer] == '.') {
    l[i++] = sourceText[posPointer++];
    return Tpoint;
  }
  //равно
  if (sourceText[posPointer] == '=') {
    l[i++] = sourceText[posPointer++];
    return Tequ;
  }

  //запятая
  if (sourceText[posPointer] == ',') {
    l[i++] = sourceText[posPointer++];
    return Tpause;
  }

  //Меньше и меньше или равно или неравно
  if (sourceText[posPointer] == '<') {
    l[i++] = sourceText[posPointer++];
    if (sourceText[posPointer] == '=') {
      l[i++] = sourceText[posPointer++];
      return Tmenequ;
    } else if (sourceText[posPointer] == '>') {
      l[i++] = sourceText[posPointer++];
      return Tnonequ;
    } else

      return Tmenee;
  }
  //Больше и больше или равно
  if (sourceText[posPointer] == '>') {
    l[i++] = sourceText[posPointer++];
    if (sourceText[posPointer] == '=') {
      l[i++] = sourceText[posPointer++];
      return Tbolequ;
    } else
      return Tbolee;
  }
  //конец файла
  if (sourceText[posPointer] == 0) return -1;
  //ничто
  l[i++] = sourceText[posPointer++];
  printerror(l);
  return 0;
}
