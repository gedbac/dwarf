#ifndef DWARF_GRAPH_NAVIGATION_GRAPH_H_
#define DWARF_GRAPH_NAVIGATION_GRAPH_H_

#include "dwarf.h"
#include "graph/graph.h"

namespace dwarf {

template <typename TNavigationNode, typename TNavigationEdge >
class NavigationGraph : public Graph<TNavigationNode, TNavigationEdge> {
  public:
    NavigationGraph();
    NavigationGraph(I32 node_list_capacity, I32 edge_list_capacity);
    NavigationGraph(BOOL digraph);
    NavigationGraph(BOOL digraph, I32 node_list_capacity, I32 edge_list_capacity);
    virtual ~NavigationGraph();
};

template <typename TNavigationNode, typename TNavigationEdge>
inline NavigationGraph<TNavigationNode, TNavigationEdge>::NavigationGraph() {}

template <typename TNavigationNode, typename TNavigationEdge>
inline NavigationGraph<TNavigationNode, TNavigationEdge>::NavigationGraph(I32 node_list_capacity, I32 edge_list_capacity)
    : Graph<TNavigationNode, TNavigationEdge>(node_list_capacity, edge_list_capacity) {}

template <typename TNavigationNode, typename TNavigationEdge>
inline NavigationGraph<TNavigationNode, TNavigationEdge>::NavigationGraph(BOOL digraph)
    : Graph<TNavigationNode, TNavigationEdge>(digraph) {}

template <typename TNavigationNode, typename TNavigationEdge>
inline NavigationGraph<TNavigationNode, TNavigationEdge>::NavigationGraph(BOOL digraph, I32 node_list_capacity, I32 edge_list_capacity)
    : Graph<TNavigationNode, TNavigationEdge>(digraph, node_list_capacity, edge_list_capacity) {}

template <typename TNavigationNode, typename TNavigationEdge>
inline NavigationGraph<TNavigationNode, TNavigationEdge>::~NavigationGraph() {}

}

#endif