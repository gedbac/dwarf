#ifndef DWARF_GRAPH_GRAPH_EDGE_H_
#define DWARF_GRAPH_GRAPH_EDGE_H_

#include "dwarf.h"

namespace dwarf {

class GraphEdge {
  public:
    GraphEdge(I32 from, I32 to);
    GraphEdge(I32 from, I32 to, F32 cost);
    virtual ~GraphEdge();
    I32 from() const;
    I32 to() const;
    F32 cost() const;
    void set_cost(F32 cost);

  private:
    I32 from_;
    I32 to_;
    F32 cost_;
};

inline GraphEdge::GraphEdge(I32 from, I32 to)
    : from_(from),
      to_(to),
      cost_(1.0f) {}

inline GraphEdge::GraphEdge(I32 from, I32 to, F32 cost)
    : from_(from),
      to_(to),
      cost_(cost) {}

inline GraphEdge::~GraphEdge() {}

inline I32 GraphEdge::from() const {
  return from_;
}

inline I32 GraphEdge::to() const {
  return to_;
}

inline F32 GraphEdge::cost() const {
  return cost_;
}

inline void GraphEdge::set_cost(F32 cost) {
  cost_ = cost;
}

}

#endif