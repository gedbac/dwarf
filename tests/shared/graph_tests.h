#ifndef DWARF_TESTS_SHARED_GRAPH_H_
#define DWARF_TESTS_SHARED_GRAPH_H_

#include <stdio.h>
#include <stdlib.h>

#include "../unit_tests.h"
#include "../../src/shared/graph.h"
#include "../../src/shared/graph_node.h"
#include "../../src/shared/graph_edge.h"

namespace dwarf {
namespace tests {
namespace shared {

using namespace dwarf::shared;

void print(Graph<GraphNode, GraphEdge>& graph) {
#ifdef DEBUG
  printf("Graph:\n");
  Graph<GraphNode, GraphEdge>::NodeIterator nodeIterator(graph);
  while (nodeIterator.HasNext()) {
    GraphNode& node = nodeIterator.Next();
    printf("%i", node.index());
    Graph<GraphNode, GraphEdge>::EdgeIterator edgeIterator(graph, node.index());
    while (edgeIterator.HasNext()) {
      GraphEdge& edge = edgeIterator.Next();
      printf("->%i", edge.to());
    }
    printf("\n");
  }
  printf("Nodes: %i Edges: %i \n", graph.NodeCount(), graph.EdgeCount());
#endif
}

TEST(should_create_graph) {

  Graph<GraphNode,GraphEdge>* graph = new Graph<GraphNode,GraphEdge>(true);

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

  print(*graph);

  ASSERT((graph->NodeCount() == 6));
  ASSERT((graph->EdgeCount() == 7));

  delete graph;

}

}
}
}

#endif