#ifndef DWARF_SHARED_DEEP_FIRST_SEARCH_H_
#define DWARF_SHARED_DEEP_FIRST_SEARCH_H_

#include "graph_search.h"
#include "list.h"
#include "stack.h"

namespace dwarf {
namespace shared {

template <typename TGraph>
class DeepFirstSearch : public GraphSearch {
  public:
  	DeepFirstSearch(const TGraph& graph);
	  virtual ~DeepFirstSearch();
    virtual bool found() const;
  	virtual int source() const;
    virtual void set_source(int source);
    virtual int target() const;
    virtual void set_target(int target);
    virtual bool Find();
    virtual const List<int>& GetPath() const;

  private:
    typedef typename TGraph::NodeType Node;
    typedef typename TGraph::EdgeType Edge;
    typedef typename TGraph::EdgeIterator GraphEdgeIterator;
    enum { VISITED, UNVISITED, NO_PARENT_ASSIGNED };
	  const TGraph& graph_;
    bool found_;
    int source_;
    int target_;
    List<int>* visited_;
    List<int>* route_;
    List<int>* path_;
    Stack<const Edge*>* stack_;
    void Initialize();
    void Cleanup(List<int>* visited, List<int>* route, List<int>* path, Stack<const Edge*>* stack);
    void PushUnvisitedEdgesToStack(int index);
};

template <typename TGraph>
inline DeepFirstSearch<TGraph>::DeepFirstSearch(const TGraph& graph)
    : graph_(graph),
      found_(false) {
  Initialize();
}

template <typename TGraph>
inline DeepFirstSearch<TGraph>::~DeepFirstSearch() {
  Cleanup(visited_, route_, path_, stack_);
}

template <typename TGraph>
inline bool DeepFirstSearch<TGraph>::found() const {
  return found_;
}

template <typename TGraph>
inline int DeepFirstSearch<TGraph>::source() const {
  return source_;
}

template <typename TGraph>
inline void DeepFirstSearch<TGraph>::set_source(int source) {
  source_ = source;
}

template <typename TGraph>
inline int DeepFirstSearch<TGraph>::target() const {
  return target_;
}

template <typename TGraph>
inline void DeepFirstSearch<TGraph>::set_target(int target) {
  target_ = target;
}

template <typename TGraph>
inline bool DeepFirstSearch<TGraph>::Find() {
  if (graph_.HasNode(source_) && graph_.HasNode(target_)) {
    const Edge* edge;
    PushUnvisitedEdgesToStack(source_);
    while (!stack_->IsEmpty()) {
      edge = stack_->Pop();
      route_->Set(edge->to(), edge->from());
      visited_->Set(edge->to(), VISITED);
      if (edge->to() == target_) {
        found_ = true;
        break;
      } else {
        PushUnvisitedEdgesToStack(edge->to());
      }
    }
    if (found_) {
      int index = target_;
      path_->Add(index);
      while (index != source_) {
        index = route_->Get(index);
        path_->Insert(0, index);
      }
    }
  }
  return found_;
}

template <typename TGraph>
inline const List<int>& DeepFirstSearch<TGraph>::GetPath() const {
  return *path_;
}

template <typename TGraph>
inline void DeepFirstSearch<TGraph>::Initialize() {
  int nodeCount = graph_.NodeCount();
  visited_ = new List<int>(nodeCount);
  for (int i = 0; i < nodeCount; ++i) {
    visited_->Add(UNVISITED);
  }
  route_ = new List<int>(nodeCount);
  for (int i = 0; i < nodeCount; ++i) {
    route_->Add(NO_PARENT_ASSIGNED);
  }
  path_ = new List<int>(nodeCount);
  int edgeCount = graph_.EdgeCount();
  stack_ = new Stack<const Edge*>(edgeCount);
}

template <typename TGraph>
inline void DeepFirstSearch<TGraph>::Cleanup(List<int>* visited,
  List<int>* route, List<int>* path, Stack<const Edge*>* stack) {
  delete visited;
  delete route;
  delete path;
  delete stack;
}

template <typename TGraph>
inline void DeepFirstSearch<TGraph>::PushUnvisitedEdgesToStack(int index) {
  GraphEdgeIterator iterator(graph_, index);
  while (iterator.HasNext()) {
    Edge& edge = iterator.Next();
    if (visited_->Get(edge.to()) == UNVISITED) {
      stack_->Push(&edge);
    }
  }
}

}
}

#endif