#include "unit_tests.h"
#include "dijkstra_search.h"
#include "graph.h"
#include "graph_node.h"
#include "graph_edge.h"

using namespace dwarf;

void print(DijkstraSearch<Graph<GraphNode,GraphEdge> >& ds) {
#ifdef DEBUG
  printf("DS: ");
  const List<I32>& path = ds.GetPath();
  List<I32>::Iterator iterator(path);
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

  graph->CreateEdge(0, 4, 2.9f);
  graph->CreateEdge(0, 5, 1.0f);
  graph->CreateEdge(1, 2, 3.1f);
  graph->CreateEdge(2, 4, 0.8f);
  graph->CreateEdge(3, 2, 3.7f);
  graph->CreateEdge(4, 1, 1.9f);
  graph->CreateEdge(4, 5, 3.0f);
  graph->CreateEdge(5, 3, 1.1f);

  DijkstraSearch<Graph<GraphNode,GraphEdge> >* search = new DijkstraSearch<Graph<GraphNode,GraphEdge> >(*graph);

  search->set_source(4);
  search->set_target(2);
  if (search->Find()) {
    print(*search);
    printf("Cost to node: %f\n", search->GetCostToTarget());
  }

  ASSERT(search->found());
  ASSERT((search->GetCostToTarget() == 5.0f));

  delete search;
  delete graph;
}