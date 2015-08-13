#include <stdio.h>
#include <stdlib.h>

#include "../tests/unit_tests.h"
#include "../tests/shared/deep_first_search_tests.h"
#include "../tests/shared/breadth_first_search_tests.h"
#include "../tests/tests.h"

int main() {

  printf("Dwarf 2015\n");

  run_all_tests();

  dwarf::tests::runAllTests();

  exit(0);
}