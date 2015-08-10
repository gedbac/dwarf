#ifndef DWARF_SHARED_BREADTH_FIRST_SEARCH_H_
#define DWARF_SHARED_BREADTH_FIRST_SEARCH_H_

namespace dwarf {
namespace shared {

template <typename TGraph>
class BreadthFirstSearch : public GraphSearch {
  public:
    BreadthFirstSearch(const TGraph& graph);
	  virtual ~BreadthFirstSearch();
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
    Queue<const Edge*>* queue_;
    void Initialize();
    void Cleanup(List<int>* visited, List<int>* route, List<int>* path, Queue<const Edge*>* queue);
    void PushUnvisitedEdgesToQueue(int index);
};

template <typename TGraph>
inline BreadthFirstSearch<TGraph>::BreadthFirstSearch(const TGraph& graph)
    : graph_(graph),
      found_(false) {
  Initialize();
}

template <typename TGraph>
inline BreadthFirstSearch<TGraph>::~BreadthFirstSearch() {
  Cleanup(visited_, route_, path_, queue_);
}

template <typename TGraph>
inline bool BreadthFirstSearch<TGraph>::found() const {
  return found_;
}

template <typename TGraph>
inline int BreadthFirstSearch<TGraph>::source() const {
  return source_;
}

template <typename TGraph>
inline void BreadthFirstSearch<TGraph>::set_source(int source) {
  source_ = source;
}

template <typename TGraph>
inline int BreadthFirstSearch<TGraph>::target() const {
  return target_;
}

template <typename TGraph>
inline void BreadthFirstSearch<TGraph>::set_target(int target) {
  target_ = target;
}

template <typename TGraph>
inline bool BreadthFirstSearch<TGraph>::Find() {
  if (graph_.HasNode(source_) && graph_.HasNode(target_)) {
    const Edge* edge;
    visited_->Set(source_, VISITED);
    PushUnvisitedEdgesToQueue(source_);
    while (!queue_->IsEmpty()) {
      edge = queue_->Pop();
      route_->Set(edge->to(), edge->from());
      if (edge->to() == target_) {
        found_ = true;
        break;
      } else {
        PushUnvisitedEdgesToQueue(edge->to());
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
inline const List<int>& BreadthFirstSearch<TGraph>::GetPath() const {
  return *path_;
}

template <typename TGraph>
inline void BreadthFirstSearch<TGraph>::Initialize() {
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
  queue_ = new Queue<const Edge*>(edgeCount);
}

template <typename TGraph>
inline void BreadthFirstSearch<TGraph>::Cleanup(List<int>* visited,
  List<int>* route, List<int>* path, Queue<const Edge*>* queue) {
  delete visited;
  delete route;
  delete path;
  delete queue;
}

template <typename TGraph>
inline void BreadthFirstSearch<TGraph>::PushUnvisitedEdgesToQueue(int index) {
  GraphEdgeIterator iterator(graph_, index);
  while (iterator.HasNext()) {
    Edge& edge = iterator.Next();
    if (visited_->Get(edge.to()) == UNVISITED) {
      queue_->Push(&edge);
      visited_->Set(edge.to(), VISITED);
    }
  }
}

}
}

#endif