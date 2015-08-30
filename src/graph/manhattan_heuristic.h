#ifndef DWARF_GRAPH_MANHATTAN_HEURISTIC_H_
#define DWARF_GRAPH_MANHATTAN_HEURISTIC_H_

#include <math.h>

#include "dwarf.h"
#include "graph/astar_heuristic.h"
#include "graph/navigation_graph_node.h"

namespace dwarf {

template <typename TNavigationGraph>
class ManhattanHeuristic : public AStarHeuristic<TNavigationGraph> {
  public:
    ManhattanHeuristic(const TNavigationGraph& graph);
    ~ManhattanHeuristic();
    virtual F32 Calculate(I32 from, I32 to);

  private:
    typedef typename TNavigationGraph::NodeType Node;
    typedef typename TNavigationGraph::EdgeType Edge;
};

template <typename TNavigationGraph>
inline ManhattanHeuristic<TNavigationGraph>::ManhattanHeuristic(const TNavigationGraph& graph)
    : AStarHeuristic<TNavigationGraph>(graph) {}

template <typename TNavigationGraph>
inline ManhattanHeuristic<TNavigationGraph>::~ManhattanHeuristic() {}

template <typename TNavigationGraph>
inline F32 ManhattanHeuristic<TNavigationGraph>::Calculate(I32 from, I32 to) {
  const TNavigationGraph& graph = AStarHeuristic<TNavigationGraph>::graph();
  Node& node1 = graph.GetNode(from);
  Node& node2 = graph.GetNode(to);
  F32 diff1 = fabs(node2.position().x - node1.position().x);
  F32 diff2 = fabs(node2.position().y - node1.position().y);
  return diff1 + diff2;
}

}

#endif