#include "unit_tests.h"
#include "graph/astar_search.h"
#include "graph/astar_heuristic.h"
#include "graph/graph.h"
#include "graph/graph_node.h"
#include "graph/graph_edge.h"

using namespace dwarf;

void print(GraphSearch& search) {
#ifdef DEBUG
  printf("Path: ");
  const List<I32>& path = search.GetPath();
  List<I32>::Iterator iterator(path);
  while (iterator.HasNext()) {
    printf("%i ", iterator.Next());
  }
  printf("\n");
#endif
}

TEST(should_find_path_using_astar_search) {

  typedef Graph<GraphNode,GraphEdge> Graph;
  typedef AStarHeuristic<Graph> AStarHeuristic;
  typedef AStarSearch<Graph,AStarHeuristic> AStarSearch;

  Graph* graph = new Graph(true, 6, 8);

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

  AStarHeuristic heuristic(*graph);

  AStarSearch* search = new AStarSearch(*graph, heuristic);

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