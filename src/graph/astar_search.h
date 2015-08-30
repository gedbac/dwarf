#ifndef DWARF_GRAPH_ASTAR_SEARCH_H_
#define	DWARF_GRAPH_ASTAR_SEARCH_H_

#include "dwarf.h"
#include "shared/list.h"
#include "shared/indexed_priority_queue.h"
#include "graph/graph_search.h"

namespace dwarf {

template <typename TGraph, typename THeuristic>
class AStarSearch : public GraphSearch {
  public:
    AStarSearch(const TGraph& graph, THeuristic& heuristic);
    virtual ~AStarSearch();
    virtual BOOL Find();
    virtual const List<I32>& GetPath();
    virtual F32 GetCostToTarget();
    virtual void Clear();

  private:
    typedef typename TGraph::NodeType Node;
    typedef typename TGraph::EdgeType Edge;
    typedef typename TGraph::EdgeIterator GraphEdgeIterator;
    const TGraph& graph_;
    THeuristic& heuristic_;
    List<F32>* cost_to_node_;
    List<Edge*>* search_frontier_;
    List<Edge*>* shortest_path_tree_;
    List<I32>* path_;
    void Initialize();
    void Cleanup();
};

template <typename TGraph, typename THeuristic>
inline AStarSearch<TGraph, THeuristic>::AStarSearch(const TGraph& graph, THeuristic& heuristic)
    : graph_(graph),
      heuristic_(heuristic) {
  Initialize();
}

template <typename TGraph, typename THeuristic>
inline AStarSearch<TGraph, THeuristic>::~AStarSearch() {
  Cleanup();
}

template <typename TGraph, typename THeuristic>
inline BOOL AStarSearch<TGraph, THeuristic>::Find() {
  IndexedPriorityQueue<F32> queue(graph_.NodeCount());
  queue.Push(source(), 0);
  while(!queue.IsEmpty()) {
    I32 next_closest_node = queue.Pop();
    shortest_path_tree_->Set(next_closest_node, search_frontier_->Get(next_closest_node));
    if (next_closest_node == target()) {
      set_found(true);
      break;
    }
    GraphEdgeIterator edgeIterator(graph_, next_closest_node);
    while (edgeIterator.HasNext()) {
      Edge& edge = edgeIterator.Next();
      F32 cost = cost_to_node_->Get(next_closest_node) + edge.cost();
      F32 heuristicCost = heuristic_.Calculate(target(), edge.cost());
      if (search_frontier_->Get(edge.to()) == NULL) {
        cost_to_node_->Set(edge.to(), cost);
        queue.Push(edge.to(), cost + heuristicCost);
        search_frontier_->Insert(edge.to(), &edge);
      }
      else if (cost < cost_to_node_->Get(edge.to())
        && shortest_path_tree_->Get(edge.to()) == NULL) {
        cost_to_node_->Set(edge.to(), cost);
        queue.Change(edge.to(), cost + heuristicCost);
        search_frontier_->Insert(edge.to(), &edge);
      }
    }
  }
  if (found()) {
    I32 index = target();
    path_->Add(index);
    while (index != source() && shortest_path_tree_->Get(index) != NULL) {
      index = shortest_path_tree_->Get(index)->from();
      path_->Insert(0, index);
    }
  }
  return found();
}

template <typename TGraph, typename THeuristic>
inline const List<I32>& AStarSearch<TGraph, THeuristic>::GetPath() {
  return *path_;
}

template <typename TGraph, typename THeuristic>
inline F32 AStarSearch<TGraph, THeuristic>::GetCostToTarget() {
  return cost_to_node_->Get(target());
}

template <typename TGraph, typename THeuristic>
inline void AStarSearch<TGraph, THeuristic>::Clear() {
  GraphSearch::Clear();
  Cleanup();
  Initialize();
}

template <typename TGraph, typename THeuristic>
inline void AStarSearch<TGraph, THeuristic>::Initialize() {
  I32 nodeCount = graph_.NodeCount();
  path_ = new List<I32>(nodeCount);
  cost_to_node_ = new List<F32>(nodeCount);
  for (I32 i = 0; i < nodeCount; i++) {
    cost_to_node_->Add(0);
  }
  search_frontier_ = new List<Edge*>();
  for (I32 i = 0; i < nodeCount; i++) {
    search_frontier_->Add(NULL);
  }
  shortest_path_tree_ = new List<Edge*>();
  for (I32 i = 0; i < nodeCount; i++) {
    shortest_path_tree_->Add(NULL);
  }
}

template <typename TGraph, typename THeuristic>
inline void AStarSearch<TGraph, THeuristic>::Cleanup() {
  delete cost_to_node_;
  delete search_frontier_;
  delete shortest_path_tree_;
  delete path_;
}

}

#endif