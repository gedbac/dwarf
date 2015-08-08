#ifndef DWARF_TESTS_SHARED_DEEP_FIRST_SEARCH_TESTS_H_
#define DWARF_TESTS_SHARED_DEEP_FIRST_SEARCH_TESTS_H_

#include <assert.h>

#include "../../src/shared/graph_node.h"
#include "../../src/shared/graph_edge.h"
#include "../../src/shared/graph.h"
#include "../../src/shared/deep_first_search.h"

namespace dwarf {
namespace tests {
namespace shared {

void should_find_path_using_dfs() {

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
    printf("DFS: ");
    const List<int>& path = dfs->GetPath();
    List<int>::Iterator iterator(path);
    while (iterator.HasNext()) {
      printf("%i ", iterator.Next());
    }
    printf("\n");
  }
  assert(dfs->found() && "path not found");
  delete dfs;
  delete graph;
}

}
}
}

#endif