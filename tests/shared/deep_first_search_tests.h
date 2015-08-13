#include "../unit_tests.h"

#include "../../src/shared/deep_first_search.h"
#include "../../src/shared/graph.h"
#include "../../src/shared/graph_node.h"
#include "../../src/shared/graph_edge.h"

TEST(ShouldFindPathUsingDFS) {

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

  DeepFirstSearch<Graph>* dfs = new DeepFirstSearch<Graph>(*graph);
  dfs->set_source(4);
  dfs->set_target(1);
  if (dfs->Find()) {
#ifdef DEBUG
    printf("DFS: ");
    const List<int>& path = dfs->GetPath();
    List<int>::Iterator iterator(path);
    while (iterator.HasNext()) {
      printf("%i ", iterator.Next());
    }
    printf("\n");
#endif
  }

  ASSERT(dfs->found());

  delete dfs;
  delete graph;
}