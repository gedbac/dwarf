#ifndef DWARF_GRAPH_ASTAR_HEURISTIC_H_
#define DWARF_GRAPH_ASTAR_HEURISTIC_H_

namespace dwarf {

template <typename TGraph>
class AStarHeuristic {
  public:
    AStarHeuristic(const TGraph& graph);
    virtual ~AStarHeuristic();
    virtual double Calculate(int from, int to);

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
inline double AStarHeuristic<TGraph>::Calculate(int from, int to) {
  return 0;
}

}

#endif