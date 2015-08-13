#include "../unit_tests.h"

#include "../../src/shared/graph_node.h"
#include "../../src/shared/graph_edge.h"
#include "../../src/shared/graph.h"
#include "../../src/shared/breadth_first_search.h"

TEST(ShouldFindPathUsingBFS) {

  using namespace dwarf::shared;

  typedef Graph<GraphNode,GraphEdge> Graph;

  Graph* graph = new Graph();
  graph->CreateNode(0);
  graph->CreateNode(1);
  graph->CreateNode(2);
  graph->CreateNode(3);
  graph->CreateNode(4);
  graph->CreateNode(5);
  graph->CreateEdge(0, 1);
  graph->CreateEdge(0, 2);
  graph->CreateEdge(1, 4);
  graph->CreateEdge(2, 3);
  graph->CreateEdge(3, 4);
  graph->CreateEdge(3, 5);
  graph->CreateEdge(4, 5);

  BreadthFirstSearch<Graph>* bfs = new BreadthFirstSearch<Graph>(*graph);
  bfs->set_source(4);
  bfs->set_target(1);
  if (bfs->Find()) {
#ifdef DEBUG
    printf("BFS: ");
    const List<int>& path = bfs->GetPath();
    List<int>::Iterator iterator(path);
    while (iterator.HasNext()) {
      printf("%i ", iterator.Next());
    }
    printf("\n");
#endif
  }

  ASSERT(bfs->found());

  delete bfs;
  delete graph;
}