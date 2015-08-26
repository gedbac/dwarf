#ifndef DWARF_GRAPH_GRAPH_EDGE_H_
#define DWARF_GRAPH_GRAPH_EDGE_H_

namespace dwarf {

class GraphEdge {
  public:
    GraphEdge(int from, int to);
    GraphEdge(int from, int to, double cost);
    virtual ~GraphEdge();
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
	    cost_(1.0) {}

inline GraphEdge::GraphEdge(int from, int to, double cost)
    : from_(from),
      to_(to),
      cost_(cost) {}

inline GraphEdge::~GraphEdge() {}

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

#endif