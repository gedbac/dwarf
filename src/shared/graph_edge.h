#ifndef DWARF_SHARED_GRAPH_EDGE_H_
#define DWARF_SHARED_GRAPH_EDGE_H_

namespace dwarf {
namespace shared {

class GraphEdge {
  public:
    GraphEdge(int from, int to);
    ~GraphEdge();
    int from() const;
    int to() const;
	  double cost() const;
    void set_cost(double cost);

  private:
    int from_;
    int to_;
	double cost_;
};

inline GraphEdge::GraphEdge(int from, int to)
    : from_(from),
      to_(to),
	  cost_(1.0) {
}

inline GraphEdge::~GraphEdge() {
}

inline int GraphEdge::from() const {
  return from_;
}

inline int GraphEdge::to() const {
  return to_;
}

inline double GraphEdge::cost() const {
  return cost_;
}

inline void GraphEdge::set_cost(double cost) {
  cost_ = cost;
}

}
}

#endif