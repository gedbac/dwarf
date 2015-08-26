#ifndef DWARF_GRAPH_NAVIGATION_GRAPH_H_
#define DWARF_GRAPH_NAVIGATION_GRAPH_H_

#include "graph.h"

namespace dwarf {

template <typename TNavigationNode, typename TNavigationEdge >
class NavigationGraph : public Graph<TNavigationNode, TNavigationEdge> {
  public:
    NavigationGraph();
    NavigationGraph(int node_list_capacity, int edge_list_capacity);
    NavigationGraph(bool digraph);
    NavigationGraph(bool digraph, int node_list_capacity, int edge_list_capacity);
    virtual ~NavigationGraph();
};

template <typename TNavigationNode, typename TNavigationEdge>
inline NavigationGraph<TNavigationNode, TNavigationEdge>::NavigationGraph() {}

template <typename TNavigationNode, typename TNavigationEdge>
inline NavigationGraph<TNavigationNode, TNavigationEdge>::NavigationGraph(int node_list_capacity, int edge_list_capacity)
	: Graph<TNavigationNode, TNavigationEdge>(node_list_capacity, edge_list_capacity) {}

template <typename TNavigationNode, typename TNavigationEdge>
inline NavigationGraph<TNavigationNode, TNavigationEdge>::NavigationGraph(bool digraph)
	: Graph<TNavigationNode, TNavigationEdge>(digraph) {}

template <typename TNavigationNode, typename TNavigationEdge>
inline NavigationGraph<TNavigationNode, TNavigationEdge>::NavigationGraph(bool digraph, int node_list_capacity, int edge_list_capacity)
	: Graph<TNavigationNode, TNavigationEdge>(digraph, node_list_capacity, edge_list_capacity) {}

template <typename TNavigationNode, typename TNavigationEdge>
inline NavigationGraph<TNavigationNode, TNavigationEdge>::~NavigationGraph() {}

}

#endif