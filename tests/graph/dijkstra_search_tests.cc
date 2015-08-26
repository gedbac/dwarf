#include "unit_tests.h"
#include "dijkstra_search.h"
#include "graph.h"
#include "graph_node.h"
#include "graph_edge.h"

using namespace dwarf;

void print(DijkstraSearch<Graph<GraphNode,GraphEdge> >& ds) {
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

TEST(should_find_path_using_dijkstra_search) {

  Graph<GraphNode,GraphEdge>* graph = new Graph<GraphNode,GraphEdge>(true, 6, 8);

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

  DijkstraSearch<Graph<GraphNode,GraphEdge> >* search = new DijkstraSearch<Graph<GraphNode,GraphEdge> >(*graph);

  search->set_source(4);
  search->set_target(2);
  if (search->Find()) {
    print(*search);
    printf("Cost to node: %f\n", search->GetCostToTarget());
  }

  ASSERT(search->found());
  ASSERT((search->GetCostToTarget() == 5.0));

  delete search;
  delete graph;
}