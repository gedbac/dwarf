#ifndef DWARF_GRAPH_EUCLID_HEURISTIC_H_
#define DWARF_GRAPH_EUCLID_HEURISTIC_H_

#include <math.h>

#include "dwarf.h"
#include "astar_heuristic.h"
#include "navigation_graph_node.h"

namespace dwarf {

template <typename TNavigationGraph>
class EuclidHeuristic : public AStarHeuristic<TNavigationGraph> {
  public:
    EuclidHeuristic(const TNavigationGraph& graph);
    ~EuclidHeuristic();
    virtual F32 Calculate(I32 from, I32 to);

  private:
    typedef typename TNavigationGraph::NodeType Node;
    typedef typename TNavigationGraph::EdgeType Edge;
};

template <typename TNavigationGraph>
inline EuclidHeuristic<TNavigationGraph>::EuclidHeuristic(const TNavigationGraph& graph)
    : AStarHeuristic<TNavigationGraph>(graph) {}

template <typename TNavigationGraph>
inline EuclidHeuristic<TNavigationGraph>::~EuclidHeuristic() {}

template <typename TNavigationGraph>
inline F32 EuclidHeuristic<TNavigationGraph>::Calculate(I32 from, I32 to) {
  const TNavigationGraph& graph = AStarHeuristic<TNavigationGraph>::graph();
  Node& node1 = graph.GetNode(from);
  Node& node2 = graph.GetNode(to);
  F32 diff1 = node2.position().x - node1.position().x;
  F32 diff2 = node2.position().y - node1.position().y;
  return sqrt(diff1*diff1 + diff2*diff2);
}

}

#endif