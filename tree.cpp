//---------------------------------------------------------------------------

#include "defs.h"
#include "semantic.h"
#include "tree.h"
//---------------------------------------------------------------------------

/*
struct data {
  Tobj t;        //тип
  Tlex id;       //идентефикатор
  int datatype;  //тип или тип возвр. значения
  union {
    int znach;       //значение для const
    int param;       //число парам для func
    int type_param;  //параметр функции - его тип(по ссылке, значению)
  };
};
*/
//в дереве

/*
struct tree {
  data data;
  tree *p;
  tree *lp;
  tree *rp;
};
*/

extern Tree *root;

extern Tree *mynode;
/*
void SetLeft(data new_data)
//создать левого потомка от текущей вершины
{
  tree *a;
  a = mynode;
  if (mynode == NULL) {
    mynode = new tree;
    root = mynode;
  } else {
    mynode->lp = new tree;
    mynode = mynode->lp;
  };
  mynode->lp = NULL;
  mynode->rp = NULL;
  mynode->p = a;
  memcpy(&mynode->data, &new_data, sizeof(data));
  return;
};

void SetRight(data new_data) {
  tree *a;
  a = mynode;
  if (mynode == NULL) {
    mynode = new tree;
    root = mynode;
  } else {
    mynode->rp = new tree;
    mynode = mynode->rp;
  };
  mynode->lp = NULL;
  mynode->rp = NULL;
  mynode->p = a;
  memcpy(&mynode->data, &new_data, sizeof(data));
  return;
};

*/

int aaa(){
    /*
  data new_data;
  Tlex l;
  strcpy(l, "my_id");
  new_data.t = typevar;
  new_data.datatype = typeint;
  strcpy(new_data.id, l);

  SetLeft(new_data);
  SetLeft(new_data);

  strcpy(l, "olya_id");
  strcpy(new_data.id, l);
  SetLeft(new_data);

  data *myd;

  myd = FindUp("myid");

  // int c=2+3 ;
  */
};
