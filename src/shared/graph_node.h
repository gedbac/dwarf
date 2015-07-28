#ifndef DWARF_SHARED_GRAPH_NIDE_H_
#define DWARF_SHARED_GRAPH_NIDE_H_

namespace dwarf {
namespace shared {

class GraphNode {
  public:
    GraphNode(int index);
    ~GraphNode();
    int index() const;

  private:
    int index_;
};

inline GraphNode::GraphNode(int index)
    : index_(index) {
}

inline GraphNode::~GraphNode() {
}

inline int GraphNode::index() const {
  return index_;
}

}
}

#endif