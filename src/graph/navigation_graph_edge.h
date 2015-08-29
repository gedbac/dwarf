#ifndef DWARF_GRAPH_NAVIGATION_GRAPH_EDGE_H_
#define DWARF_GRAPH_NAVIGATION_GRAPH_EDGE_H_

#include "graph_edge.h"

namespace dwarf {

template <typename TExtraInfo = void*>
class NavigationGraphEdge : public GraphEdge {
  public:
    NavigationGraphEdge(int from, int to);
    NavigationGraphEdge(int from, int to, double cost);
    ~NavigationGraphEdge();
    TExtraInfo extra_info() const;
    void set_extra_info(TExtraInfo extraInfo);

  private:
    Point position_;
    TExtraInfo extra_info_;
};

template <typename TExtraInfo>
inline NavigationGraphEdge<TExtraInfo>::NavigationGraphEdge(int from, int to)
    : GraphEdge(from, to, 1.0) {}

template <typename TExtraInfo>
inline NavigationGraphEdge<TExtraInfo>::NavigationGraphEdge(int from, int to, double cost)
    : GraphEdge(from, to, cost) {}

template <typename TExtraInfo>
inline NavigationGraphEdge<TExtraInfo>::~NavigationGraphEdge() {}

template <typename TExtraInfo>
inline TExtraInfo NavigationGraphEdge<TExtraInfo>::extra_info() const {
  return extra_info_;
}

template <typename TExtraInfo>
inline void NavigationGraphEdge<TExtraInfo>::set_extra_info(TExtraInfo extra_info) {
  extra_info_ = extra_info;
}

}

#endif