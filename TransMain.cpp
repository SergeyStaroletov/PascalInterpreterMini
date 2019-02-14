
#include <exception>
#include "defs.h"
#include "diagram.h"
#include "scaner.h"
#include "semantic.h"
#include "tree.h"

//---------------------------------------------------------------------------
int main(int argc, char **argv) {
  printf("'TransMain' Mini-Pascal interpretator. Version 1.0.15\n");
  printf("Copyright (c) 2004 Staroletov Sergey, Powt-13\n");
  printf(
      "Supports: integer/boolean types/operations, functions with params, := "
      "and while.\n\n");
  fflush(stdout);
  if (argc == 1) {
    printf("Error: no input given. Usage: transmain filename\n");
    exit(1);
  } else
    getData(argv[1]);

  try {
    syntax();

    printf("\nNormal shutdown.\n");
  } catch (std::exception &e) {
    printf("\nShutdown with runtime error:");
    printf("%s.", e.what());
  };

  printTree();
  fflush(stdout);
  return 0;
}
