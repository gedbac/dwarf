#include "navigation_graph_node.h"
#include "navigation_graph_edge.h"
#include "navigation_graph.h"
#include "euclid_heuristic.h"
#include "point.h"

using namespace dwarf;

TEST(should_calculate_cost_using_euclid_heuristic) {

  typedef NavigationGraphNode<void*> NavigationGraphNode;
  typedef NavigationGraphEdge<void*> NavigationGraphEdge;
  typedef NavigationGraph<NavigationGraphNode, NavigationGraphEdge> NavigationGraph;

  NavigationGraph graph(true);

  NavigationGraphNode& node1 = graph.CreateNode(0);
  node1.set_position(Point(0.0f, 0.0f));
  NavigationGraphNode& node2 = graph.CreateNode(1);
  node2.set_position(Point(10.0f, 0.0f));

  EuclidHeuristic<NavigationGraph> heuristic(graph);

  F32 cost = heuristic.Calculate(0, 1);

  ASSERT((cost == 10.0f));
}


