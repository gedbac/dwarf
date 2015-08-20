#ifndef DWARF_TESTS_SHARED_BREADTH_FIRST_SEARCH_H_
#define DWARF_TESTS_SHARED_BREADTH_FIRST_SEARCH_H_

#include "../unit_tests.h"

#include "../../src/shared/graph_node.h"
#include "../../src/shared/graph_edge.h"
#include "../../src/shared/graph.h"
#include "../../src/shared/breadth_first_search.h"

namespace dwarf {
namespace tests {
namespace shared {

using namespace dwarf::shared;

void print(BreadthFirstSearch<Graph<GraphNode,GraphEdge> >& bfs) {
#ifdef DEBUG
    printf("BFS: ");
    const List<int>& path = bfs.GetPath();
    List<int>::Iterator iterator(path);
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

  BreadthFirstSearch<Graph<GraphNode,GraphEdge> >* bfs = new BreadthFirstSearch<Graph<GraphNode,GraphEdge> >(*graph);
  bfs->set_source(4);
  bfs->set_target(1);
  if (bfs->Find()) {
    print(*bfs);
  }

  ASSERT(bfs->found());

  delete bfs;
  delete graph;
}

}
}
}

#endif