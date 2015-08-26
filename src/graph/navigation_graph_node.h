#ifndef DWARF_GRAPH_NAVIGATION_GRAPH_NODE_H_
#define DWARF_GRAPH_NAVIGATION_GRAPH_NODE_H_

#include "graph_node.h"
#include "point.h"

namespace dwarf {

template <typename TExtraInfo = void*>
class NavigationGraphNode : public GraphNode {
  public:
    NavigationGraphNode(int index);
    NavigationGraphNode(int index, Point position);
	  virtual ~NavigationGraphNode();
	  Point position() const;
    void set_position(Point position);
    TExtraInfo extra_info() const;
    void set_extra_info(TExtraInfo extraInfo);

  private:
    Point position_;
    TExtraInfo extra_info_;
};

template <typename TExtraInfo>
inline NavigationGraphNode<TExtraInfo>::NavigationGraphNode(int index)
    : GraphNode(index),
      position_(Point()) {}

template <typename TExtraInfo>
inline NavigationGraphNode<TExtraInfo>::NavigationGraphNode(int index, Point position)
    : GraphNode(index),
      position_(position) {}

template <typename TExtraInfo>
inline NavigationGraphNode<TExtraInfo>::~NavigationGraphNode() {}

template <typename TExtraInfo>
inline Point NavigationGraphNode<TExtraInfo>::position() const {
  return position_;
}

template <typename TExtraInfo>
inline void NavigationGraphNode<TExtraInfo>::set_position(Point position) {
  position_ = position;
}

template <typename TExtraInfo>
inline TExtraInfo NavigationGraphNode<TExtraInfo>::extra_info() const {
  return extra_info_;
}

template <typename TExtraInfo>
inline void NavigationGraphNode<TExtraInfo>::set_extra_info(TExtraInfo extra_info) {
  extra_info_ = extra_info;
}

}

#endif