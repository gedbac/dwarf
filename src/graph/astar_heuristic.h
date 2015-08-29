#ifndef DWARF_GRAPH_ASTAR_HEURISTIC_H_
#define DWARF_GRAPH_ASTAR_HEURISTIC_H_

#include "dwarf.h"

namespace dwarf {

template <typename TGraph>
class AStarHeuristic {
  public:
    AStarHeuristic(const TGraph& graph);
    virtual ~AStarHeuristic();
    virtual F32 Calculate(I32 from, I32 to);

  protected:
    const TGraph& graph() const;

  private:
    const TGraph& graph_;
};

template <typename TGraph>
inline AStarHeuristic<TGraph>::AStarHeuristic(const TGraph& graph)
    : graph_(graph) {}

template <typename TGraph>
inline AStarHeuristic<TGraph>::~AStarHeuristic() {}

template <typename TGraph>
inline const TGraph& AStarHeuristic<TGraph>::graph() const {
  return graph_;
}

template <typename TGraph>
inline F32 AStarHeuristic<TGraph>::Calculate(I32 from, I32 to) {
  return 0;
}

}

#endif