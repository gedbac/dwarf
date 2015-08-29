#ifndef DWARF_GRAPH_DEEP_FIRST_SEARCH_H_
#define DWARF_GRAPH_DEEP_FIRST_SEARCH_H_

#include "graph_search.h"
#include "list.h"
#include "stack.h"

namespace dwarf {

template <typename TGraph>
class DeepFirstSearch : public GraphSearch {
  public:
  	DeepFirstSearch(const TGraph& graph);
    virtual ~DeepFirstSearch();
    virtual bool Find();
    virtual const List<int>& GetPath() const;
    virtual void Clear();

  private:
    typedef typename TGraph::NodeType Node;
    typedef typename TGraph::EdgeType Edge;
    typedef typename TGraph::EdgeIterator GraphEdgeIterator;
    enum { VISITED, UNVISITED, NO_PARENT_ASSIGNED };
    const TGraph& graph_;
    List<int>* visited_;
    List<int>* route_;
    List<int>* path_;
    Stack<const Edge*>* stack_;
    void Initialize();
    void Cleanup();
    void PushUnvisitedEdgesToStack(int index);
};

template <typename TGraph>
inline DeepFirstSearch<TGraph>::DeepFirstSearch(const TGraph& graph)
    : graph_(graph) {
  Initialize();
}

template <typename TGraph>
inline DeepFirstSearch<TGraph>::~DeepFirstSearch() {
  Cleanup();
}

template <typename TGraph>
inline bool DeepFirstSearch<TGraph>::Find() {
  if (graph_.HasNode(source()) && graph_.HasNode(target())) {
    const Edge* edge;
    PushUnvisitedEdgesToStack(source());
    while (!stack_->IsEmpty()) {
      edge = stack_->Pop();
      route_->Set(edge->to(), edge->from());
      visited_->Set(edge->to(), VISITED);
      if (edge->to() == target()) {
        set_found(true);
        break;
      } else {
        PushUnvisitedEdgesToStack(edge->to());
      }
    }
    if (found()) {
      int index = target();
      path_->Add(index);
      while (index != source()) {
        index = route_->Get(index);
        path_->Insert(0, index);
      }
    }
  }
  return found();
}

template <typename TGraph>
inline const List<int>& DeepFirstSearch<TGraph>::GetPath() const {
  return *path_;
}

template <typename TGraph>
inline void DeepFirstSearch<TGraph>::Clear() {
  GraphSearch::Clear();
  Cleanup();
  Initialize();
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
inline void DeepFirstSearch<TGraph>::Cleanup() {
  delete visited_;
  delete route_;
  delete path_;
  delete stack_;
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

#endif