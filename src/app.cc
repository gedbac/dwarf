#include <stdio.h>
#include <stdlib.h>

#include "../tests/tests.h"

int main() {

  printf("Dwarf 2015\n");

  dwarf::tests::runAllTests();

  exit(0);
}