#include <stdio.h>
#include <stdlib.h>

#include "unit_tests.h"

#include "shared/list_tests.cc"
#include "shared/stack_tests.cc"
#include "shared/queue_tests.cc"
#include "shared/priority_queue_tests.cc"
#include "shared/indexed_priority_queue_tests.cc"
#include "shared/clock_tests.cc"
#include "graph/graph_tests.cc"
#include "graph/deep_first_search_tests.cc"
#include "graph/breadth_first_search_tests.cc"
#include "graph/dijkstra_search_tests.cc"
#include "graph/astar_search_tests.cc"
#include "graph/euclid_heuristic_tests.cc"
#include "graph/manhattan_heuristic_tests.cc"

int main() {

  printf("Dwarf Unit Test Runner 2015\n");

  run_all_tests();

  exit(0);
}