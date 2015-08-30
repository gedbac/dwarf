#ifndef DWARF_GRAPH_NAVIGATION_GRAPH_EDGE_H_
#define DWARF_GRAPH_NAVIGATION_GRAPH_EDGE_H_

#include "dwarf.h"
#include "graph/graph_edge.h"

namespace dwarf {

template <typename TExtraInfo = void*>
class NavigationGraphEdge : public GraphEdge {
  public:
    NavigationGraphEdge(I32 from, I32 to);
    NavigationGraphEdge(I32 from, I32 to, F32 cost);
    ~NavigationGraphEdge();
    TExtraInfo extra_info() const;
    void set_extra_info(TExtraInfo extraInfo);

  private:
    Point position_;
    TExtraInfo extra_info_;
};

template <typename TExtraInfo>
inline NavigationGraphEdge<TExtraInfo>::NavigationGraphEdge(I32 from, I32 to)
    : GraphEdge(from, to, 1.0f) {}

template <typename TExtraInfo>
inline NavigationGraphEdge<TExtraInfo>::NavigationGraphEdge(I32 from, I32 to, F32 cost)
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