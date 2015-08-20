#include <stdio.h>
#include <stdlib.h>

#include "unit_tests.h"

#include "shared/list_tests.h"
#include "shared/stack_tests.h"
#include "shared/queue_tests.h"
#include "shared/priority_queue_tests.h"
#include "shared/indexed_priority_queue_tests.h"
#include "shared/graph_tests.h"
#include "shared/deep_first_search_tests.h"
#include "shared/breadth_first_search_tests.h"
#include "shared/dijkstra_search_tests.h"

int main() {

  printf("Dwarf Unit Test Runner 2015\n");

  run_all_tests();
   
  exit(0);
}