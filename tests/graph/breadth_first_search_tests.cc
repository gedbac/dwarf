#include "unit_tests.h"
#include "graph/graph_node.h"
#include "graph/graph_edge.h"
#include "graph/graph.h"
#include "graph/breadth_first_search.h"

using namespace dwarf;

void print(BreadthFirstSearch<Graph<GraphNode,GraphEdge> >& bfs) {
#ifdef DEBUG
  printf("BFS: ");
  const List<I32>& path = bfs.GetPath();
  List<I32>::Iterator iterator(path);
  while (iterator.HasNext()) {
    printf("%i ", iterator.Next());
  }
  printf("\n");
#endif
}

TEST(should_find_path_using_bfs) {

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

  BreadthFirstSearch<Graph<GraphNode,GraphEdge> >* search = new BreadthFirstSearch<Graph<GraphNode,GraphEdge> >(*graph);
  search->set_source(4);
  search->set_target(1);
  if (search->Find()) {
    print(*search);
  }

  ASSERT(search->found());

  delete search;
  delete graph;
}