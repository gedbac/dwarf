#ifndef DWARF_TESTS_SHARED_DIJKSTRA_SEARCH_H_
#define DWARF_TESTS_SHARED_DIJKSTRA_SEARCH_H_

#include "../unit_tests.h"

#include "../../src/shared/dijkstra_search.h"
#include "../../src/shared/graph.h"
#include "../../src/shared/graph_node.h"
#include "../../src/shared/graph_edge.h"

namespace dwarf {
namespace tests {
namespace shared {

using namespace dwarf::shared;

typedef Graph<GraphNode,GraphEdge> Graph;

void print(DijkstraSearch<Graph>& ds) {
#ifdef DEBUG
  printf("DS: ");
  const List<int>& path = ds.GetPath();
  List<int>::Iterator iterator(path);
  while (iterator.HasNext()) {
    printf("%i ", iterator.Next());
  }
  printf("\n");
#endif
}

SKIP_TEST(should_find_path_using_dijkstra_search) {

  Graph* graph = new Graph(true, 6, 8);

  graph->CreateNode(0);
  graph->CreateNode(1);
  graph->CreateNode(2);
  graph->CreateNode(3);
  graph->CreateNode(4);
  graph->CreateNode(5);

  graph->CreateEdge(0, 4, 2.9);
  graph->CreateEdge(0, 5, 1.0);
  graph->CreateEdge(1, 2, 3.1);
  graph->CreateEdge(2, 4, 0.8);
  graph->CreateEdge(3, 2, 3.7);
  graph->CreateEdge(4, 1, 1.9);
  graph->CreateEdge(4, 5, 3.0);
  graph->CreateEdge(5, 3, 1.1);

  DijkstraSearch<Graph>* ds = new DijkstraSearch<Graph>(*graph);

  ds->set_source(4);
  ds->set_target(2);
  if (ds->Find()) {
    print(*ds);
    printf("Cost to node: %f\n", ds->GetCostToTarget());
  }

  ASSERT(ds->found());
  ASSERT((ds->GetCostToTarget() == 5.0));

  delete ds;
  delete graph;
}

}
}
}

#endif