//---------------------------------------------------------------------------

#include "defs.h"
#include "semantic.h"
#include "tree.h"
//---------------------------------------------------------------------------

/*
struct data {
  Tobj t;        //���
  Tlex id;       //�������������
  int datatype;  //��� ��� ��� �����. ��������
  union {
    int znach;       //�������� ��� const
    int param;       //����� ����� ��� func
    int type_param;  //�������� ������� - ��� ���(�� ������, ��������)
  };
};
*/
//� ������

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
//������� ������ ������� �� ������� �������
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
