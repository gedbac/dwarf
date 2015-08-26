#include "unit_tests.h"
#include "deep_first_search.h"
#include "graph.h"
#include "graph_node.h"
#include "graph_edge.h"

using namespace dwarf;

void print(DeepFirstSearch<Graph<GraphNode,GraphEdge> >& dfs) {
#ifdef DEBUG
    printf("DFS: ");
    const List<int>& path = dfs.GetPath();
    List<int>::Iterator iterator(path);
    while (iterator.HasNext()) {
      printf("%i ", iterator.Next());
    }
    printf("\n");
#endif
}

TEST(should_find_path_using_dfs) {

  Graph<GraphNode,GraphEdge>* graph = new Graph<GraphNode,GraphEdge>();

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

  DeepFirstSearch<Graph<GraphNode,GraphEdge> >* search = new DeepFirstSearch<Graph<GraphNode,GraphEdge> >(*graph);
  search->set_source(4);
  search->set_target(1);
  if (search->Find()) {
    print(*search);
  }

  ASSERT(search->found());

  delete search;
  delete graph;
}