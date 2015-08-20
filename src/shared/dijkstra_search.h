#ifndef DWARF_SHARED_DIJKSTRA_SEARCH_H_
#define DWARF_SHARED_DIJKSTRA_SEARCH_H_

#include "graph_search.h"
#include "list.h"
#include "indexed_priority_queue.h"

namespace dwarf {
namespace shared {

template <typename TGraph>
class DijkstraSearch : public GraphSearch {
  public:
    DijkstraSearch(const TGraph& graph);
	  virtual ~DijkstraSearch();
    virtual bool found() const;
  	virtual int source() const;
    virtual void set_source(int source);
    virtual int target() const;
    virtual void set_target(int target);
    virtual bool Find();
    virtual const List<int>& GetPath() const;
    virtual double GetCostToTarget() const;

  private:
    typedef typename TGraph::NodeType Node;
    typedef typename TGraph::EdgeType Edge;
    typedef typename TGraph::EdgeIterator GraphEdgeIterator;
	  const TGraph& graph_;
    bool found_;
    int source_;
    int target_;
    List<double>* costToNode_;
    List<Edge*>* searchFrontier_;
    List<Edge*>* shortestPathTree_;
    List<int>* path_;
    void Initialize();
    void Cleanup(List<double>* costToNode, List<Edge*>* searchFrontier,
      List<Edge*>* shortestPathTree, List<int>* path);
};

template <typename TGraph>
inline DijkstraSearch<TGraph>::DijkstraSearch(const TGraph& graph)
    : graph_(graph),
      found_(false) {
  Initialize();
}

template <typename TGraph>
inline DijkstraSearch<TGraph>::~DijkstraSearch() {
  Cleanup(costToNode_, searchFrontier_, shortestPathTree_, path_);
}

template <typename TGraph>
inline bool DijkstraSearch<TGraph>::found() const {
  return found_;
}

template <typename TGraph>
inline int DijkstraSearch<TGraph>::source() const {
  return source_;
}

template <typename TGraph>
inline void DijkstraSearch<TGraph>::set_source(int source) {
  source_ = source;
}

template <typename TGraph>
inline int DijkstraSearch<TGraph>::target() const {
  return target_;
}

template <typename TGraph>
inline void DijkstraSearch<TGraph>::set_target(int target) {
  target_ = target;
}

template <typename TGraph>
inline bool DijkstraSearch<TGraph>::Find() {
  IndexedPriorityQueue<double> ipq(graph_.NodeCount());
  ipq.Push(source(), 0);
  while(!ipq.IsEmpty()) {
    int nextClosestNode = ipq.Pop();
    shortestPathTree_->Set(nextClosestNode, searchFrontier_->Get(nextClosestNode));
    if (nextClosestNode == target()) {
      found_ = true;
      break;
    }
    GraphEdgeIterator edgeIterator(graph_, nextClosestNode);
    while (edgeIterator.HasNext()) {
      Edge& edge = edgeIterator.Next();
      double newCost = costToNode_->Get(nextClosestNode) + edge.cost();
      if (searchFrontier_->Get(edge.to()) == NULL) {
        costToNode_->Set(edge.to(), newCost);
        ipq.Push(edge.to(), newCost);
        searchFrontier_->Insert(edge.to(), &edge);
      }
      else if (newCost < costToNode_->Get(edge.to())
        && shortestPathTree_->Get(edge.to()) == NULL) {
        costToNode_->Set(edge.to(), newCost);
        ipq.Change(edge.to(), newCost);
        searchFrontier_->Insert(edge.to(), &edge);
      }
    }
  }
  if (found_) {
    int index = target();
    path_->Add(index);
    while (index != source() && shortestPathTree_->Get(index) != NULL) {
      index = shortestPathTree_->Get(index)->from();
      path_->Insert(0, index);
    }
  }
  return found_;
}

template <typename TGraph>
inline const List<int>& DijkstraSearch<TGraph>::GetPath() const {
  return *path_;
}

template <typename TGraph>
inline double DijkstraSearch<TGraph>::GetCostToTarget() const {
  return costToNode_->Get(target());
}

template <typename TGraph>
inline void DijkstraSearch<TGraph>::Initialize() {
  int nodeCount = graph_.NodeCount();
  path_ = new List<int>(nodeCount);
  costToNode_ = new List<double>(nodeCount);
  for (int i = 0; i < nodeCount; i++) {
    costToNode_->Add(0);
  }
  searchFrontier_ = new List<Edge*>();
  for (int i = 0; i < nodeCount; i++) {
    searchFrontier_->Add(NULL);
  }
  shortestPathTree_ = new List<Edge*>();
  for (int i = 0; i < nodeCount; i++) {
    shortestPathTree_->Add(NULL);
  }
}

template <typename TGraph>
inline void DijkstraSearch<TGraph>::Cleanup(List<double>* costToNode, List<Edge*>* searchFrontier,
  List<Edge*>* shortestPathTree, List<int>* path) {
  delete costToNode;
  delete searchFrontier;
  delete shortestPathTree;
  delete path;
}

}
}

#endif