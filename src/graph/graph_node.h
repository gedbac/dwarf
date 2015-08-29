#ifndef DWARF_GRAPH_GRAPH_NIDE_H_
#define DWARF_GRAPH_GRAPH_NIDE_H_

#include "dwarf.h"

namespace dwarf {

class GraphNode {
  public:
    GraphNode(I32 index);
    virtual ~GraphNode();
    I32 index() const;

  private:
    I32 index_;
};

inline GraphNode::GraphNode(I32 index)
    : index_(index) {}

inline GraphNode::~GraphNode() {}

inline I32 GraphNode::index() const {
  return index_;
}

}

#endif