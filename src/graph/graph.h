#ifndef DWARF_GRAPH_GRAPH_H_
#define DWARF_GRAPH_GRAPH_H_

#include "dwarf.h"
#include "list.h"

namespace dwarf {

template <typename TNode, typename TEdge>
class Graph {
  public:
    typedef TNode NodeType;
    typedef TEdge EdgeType;
    typedef List<TNode*> NodeList;
    typedef List<TEdge*> NodeEdgeList;
    typedef List<NodeEdgeList*> EdgeList;
    typedef typename NodeList::Iterator NodeListIterator;
    typedef typename NodeEdgeList::Iterator NodeEdgeListIterator;
    typedef typename EdgeList::Iterator EdgeListIterator;
    Graph();
    Graph(I32 node_list_capacity, I32 edge_list_capacity);
    Graph(BOOL digraph);
    Graph(BOOL digraph, I32 node_list_capacity, I32 edge_list_capacity);
    virtual ~Graph();
    BOOL digraph() const;
    I32 GetNextNodeIndex();
    TNode& CreateNode(I32 index);
    TNode& GetNode(I32 index) const;
    BOOL HasNode(I32 index) const;
    void RemoveNode(I32 index);
    I32 NodeCount() const;
    TEdge& CreateEdge(I32 from, I32 to);
    TEdge& CreateEdge(I32 from, I32 to, F32 cost);
    TEdge& GetEdge(I32 from, I32 to) const;
    BOOL HasEdge(I32 from, I32 to) const;
    void RemoveEdge(I32 from, I32 to);
    I32 EdgeCount(I32 index) const;
    I32 EdgeCount() const;
    void Clear();

    class NodeIterator {
      public:
        NodeIterator(const Graph<TNode,TEdge>& graph);
        ~NodeIterator();
        BOOL HasNext();
        TNode& Next();

      private:
        I32 position_;
        const Graph<TNode,TEdge>& graph_;
    };

    friend class NodeIterator;

    class EdgeIterator {
      public:
        EdgeIterator(const Graph<TNode,TEdge>& graph, I32 index);
        ~EdgeIterator();
        BOOL HasNext();
        TEdge& Next();

      private:
        I32 position_;
        const Graph<TNode,TEdge>& graph_;
        NodeEdgeList* node_edges_;
    };

    friend class EdgeIterator;

  private:
    BOOL digraph_;
    I32 node_list_capacity_;
    I32 edge_list_capacity_;
    I32 next_node_index_;
    NodeList* nodes_;
    EdgeList* edges_;
    void Initialize(I32 node_list_capacity, I32 edge_list_capacity);
    void Cleanup(NodeList* nodes, EdgeList* edges);
    void DeleteNodes(NodeList* nodes);
    void DeleteEdges(EdgeList* edges);
};

template <typename TNode, typename TEdge>
inline Graph<TNode,TEdge>::Graph()
    : digraph_(false),
      node_list_capacity_(4),
      edge_list_capacity_(4),
      next_node_index_(0) {
  Initialize(node_list_capacity_, edge_list_capacity_);
}

template <typename TNode, typename TEdge>
inline Graph<TNode,TEdge>::Graph(I32 node_list_capacity, I32 edge_list_capacity)
    : digraph_(false),
      node_list_capacity_(node_list_capacity),
      edge_list_capacity_(edge_list_capacity),
      next_node_index_(0) {
  Initialize(node_list_capacity_, edge_list_capacity_);
}

template <typename TNode, typename TEdge>
inline Graph<TNode,TEdge>::Graph(BOOL digraph)
    : digraph_(digraph),
      node_list_capacity_(4),
      edge_list_capacity_(4),
      next_node_index_(0) {
  Initialize(node_list_capacity_, edge_list_capacity_);
}

template <typename TNode, typename TEdge>
inline Graph<TNode,TEdge>::Graph(BOOL digraph, I32 node_list_capacity,
  I32 edge_list_capacity)
    : digraph_(digraph),
      node_list_capacity_(node_list_capacity),
      edge_list_capacity_(edge_list_capacity),
      next_node_index_(0) {
  Initialize(node_list_capacity_, edge_list_capacity_);
}

template <typename TNode, typename TEdge>
inline Graph<TNode,TEdge>::~Graph() {
  Cleanup(nodes_, edges_);
}

template <typename TNode, typename TEdge>
inline BOOL Graph<TNode,TEdge>::digraph() const {
  return digraph_;
}

template <typename TNode, typename TEdge>
inline I32 Graph<TNode,TEdge>::GetNextNodeIndex() {
  return next_node_index_;
}

template <typename TNode, typename TEdge>
inline TNode& Graph<TNode,TEdge>::CreateNode(I32 index) {
  assert(index >= 0 && index >= nodes_->length() && "node's index is invalid");
  assert(!HasNode(index) && "attempting to add a dublicate node");
  TNode* node = new TNode(index);
  nodes_->Insert(node->index(), node);
  edges_->Insert(node->index(), new NodeEdgeList());
  next_node_index_ = index + 1;
  return *node;
}

template <typename TNode, typename TEdge>
inline TNode& Graph<TNode,TEdge>::GetNode(I32 index) const {
  assert(index >= 0 && index < nodes_->length() && "node's index is invalid");
  TNode* node = nodes_->Get(index);
  assert(node != NULL && "node doesn't exists");
  return *node;
}

template <typename TNode, typename TEdge>
inline BOOL Graph<TNode,TEdge>::HasNode(I32 index) const {
  if (index >= 0 && index < nodes_->length()) {
    TNode* node = nodes_->Get(index);
    if (node != NULL) {
      return true;
    }
  }
  return false;
}

template <typename TNode, typename TEdge>
inline void Graph<TNode,TEdge>::RemoveNode(I32 index) {
  assert(index >= 0 && index < nodes_->length() && "node's index is invalid");
  TNode* node = nodes_->Get(index);
  if (node != NULL) {
    nodes_->Set(index, NULL);
    delete node;
  }
  TEdge* edge;
  NodeEdgeList* node_edges = edges_->Get(index);
  if (node_edges != NULL) {
    NodeEdgeListIterator iterator(*node_edges);
    while (iterator.HasNext()) {
      edge = iterator.Next();
      delete edge;
    }
    edges_->Set(index, NULL);
    delete node_edges;
  }
  EdgeListIterator edgeIterator(*edges_);
  while (edgeIterator.HasNext()) {
    node_edges = edgeIterator.Next();
    if (node_edges != NULL) {
      NodeEdgeListIterator nodeEdgeIterator(*node_edges);
      while (nodeEdgeIterator.HasNext()) {
        edge = nodeEdgeIterator.Next();
        if (edge != NULL && edge->to() == index) {
          I32 index = node_edges->IndexOf(edge);
          node_edges->Set(index, NULL);
          delete edge;
        }
      }
    }
  }
}

template <typename TNode, typename TEdge>
inline I32 Graph<TNode,TEdge>::NodeCount() const {
  I32 count = 0;
  TNode* node;
  NodeListIterator iterator(*nodes_);
  while (iterator.HasNext()) {
    node = iterator.Next();
    if (node != NULL) {
      count++;
    }
  }
  return count;
}

template <typename TNode, typename TEdge>
inline TEdge& Graph<TNode,TEdge>::CreateEdge(I32 from, I32 to) {
  assert(from >= 0 && from < nodes_->length() && "node's 'from' index is invalid");
  assert(to >= 0 && to < nodes_->length() && "node's 'to' index is invalid");
  assert(!HasEdge(from, to) && "attempting to add a dublicate edge");
  TEdge* edge = new TEdge(from, to);
  NodeEdgeList* node_edges = edges_->Get(from);
  node_edges->Add(edge);
  if (!digraph_) {
    node_edges = edges_->Get(to);
    edge = new TEdge(to, from);
    node_edges->Add(edge);
  }
  return *edge;
}

template <typename TNode, typename TEdge>
inline TEdge& Graph<TNode,TEdge>::CreateEdge(I32 from, I32 to, F32 cost) {
  assert(from >= 0 && from < nodes_->length() && "node's 'from' index is invalid");
  assert(to >= 0 && to < nodes_->length() && "node's 'to' index is invalid");
  assert(!HasEdge(from, to) && "attempting to add a dublicate edge");
  TEdge* edge = new TEdge(from, to, cost);
  NodeEdgeList* node_edges = edges_->Get(from);
  node_edges->Add(edge);
  if (!digraph_) {
    node_edges = edges_->Get(to);
    edge = new TEdge(to, from, cost);
    node_edges->Add(edge);
  }
  return *edge;
}

template <typename TNode, typename TEdge>
inline TEdge& Graph<TNode,TEdge>::GetEdge(I32 from, I32 to) const {
  assert(from >= 0 && from < nodes_->length() && "node's 'from' index is invalid");
  assert(to >= 0 && to < nodes_->length() && "node's 'to' index is invalid");
  NodeEdgeList* node_edges = edges_->Get(from);
  if (node_edges != NULL) {
    TEdge* edge;
    NodeEdgeListIterator iterator(*node_edges);
    while (iterator.HasNext()) {
      edge = iterator.Next();
      if (edge != NULL && edge->to() == to) {
        return *edge;
      }
    }
  }
  assert(0 && "edge doesn't exists");
}

template <typename TNode, typename TEdge>
inline BOOL Graph<TNode,TEdge>::HasEdge(I32 from, I32 to) const {
  if (from >= 0 && from < nodes_->length() && to >= 0 && to < nodes_->length()) {
    NodeEdgeList* node_edges = edges_->Get(from);
    TEdge* edge;
    NodeEdgeListIterator iterator(*node_edges);
    while (iterator.HasNext()) {
      edge = iterator.Next();
      if (edge != NULL && edge->to() == to) {
        return true;
      }
    }
  }
  return false;
}

template <typename TNode, typename TEdge>
inline void Graph<TNode,TEdge>::RemoveEdge(I32 from, I32 to) {
  assert(from >= 0 && from < nodes_->length() && "node's 'from' index is invalid");
  assert(to >= 0 && to < nodes_->length() && "node's 'to' index is invalid");
  NodeEdgeList* node_edges = edges_->Get(from);
  if (node_edges != NULL) {
    NodeEdgeListIterator iterator(*node_edges);
    TEdge* edge;
    while (iterator.HasNext()) {
      edge = iterator.Next();
      if (edge != NULL && edge->to() == to) {
        I32 index = node_edges->IndexOf(edge);
        node_edges->Set(index, NULL);
        delete edge;
        break;
      }
    }
  }
}

template <typename TNode, typename TEdge>
inline I32 Graph<TNode,TEdge>::EdgeCount(I32 index) const {
  assert(index >= 0 && index < nodes_->length() && "node's index is invalid");
  I32 count = 0;
  NodeEdgeList* node_edges = edges_->Get(index);
  if (node_edges != NULL) {
    NodeEdgeListIterator iterator(*node_edges);
    TEdge* edge;
    while (iterator.HasNext()) {
      edge = iterator.Next();
      if (edge != NULL) {
        count++;
      }
    }
  }
  return count;
}

template <typename TNode, typename TEdge>
inline I32 Graph<TNode,TEdge>::EdgeCount() const {
  I32 count = 0;
  NodeEdgeList* node_edges;
  TEdge* edge;
  EdgeListIterator edgeIterator(*edges_);
  while (edgeIterator.HasNext()) {
    node_edges = edgeIterator.Next();
    if (node_edges != NULL) {
      NodeEdgeListIterator nodeEdgeIterator(*node_edges);
      while (nodeEdgeIterator.HasNext()) {
        edge = nodeEdgeIterator.Next();
        if (edge != NULL) {
          count++;
        }
      }
    }
  }
  return count;
}

template <typename TNode, typename TEdge>
inline void Graph<TNode,TEdge>::Clear() {
  Cleanup(nodes_, edges_);
  Initialize(node_list_capacity_, edge_list_capacity_);
}

template <typename TNode, typename TEdge>
inline void Graph<TNode,TEdge>::Initialize(I32 node_list_capacity, I32 edge_list_capacity) {
  nodes_ = new NodeList(node_list_capacity);
  edges_ = new EdgeList(edge_list_capacity);
}

template <typename TNode, typename TEdge>
inline void Graph<TNode,TEdge>::Cleanup(NodeList* nodes, EdgeList* edges) {
  DeleteNodes(nodes);
  DeleteEdges(edges);
}

template <typename TNode, typename TEdge>
inline void Graph<TNode,TEdge>::DeleteNodes(NodeList* nodes) {
  TNode* node;
  NodeListIterator nodeIterator(*nodes);
  while (nodeIterator.HasNext()) {
    node = nodeIterator.Next();
    delete node;
  }
  delete nodes;
}

template <typename TNode, typename TEdge>
inline void Graph<TNode,TEdge>::DeleteEdges(EdgeList* edges) {
  NodeEdgeList* node_edges;
  TEdge* edge;
  EdgeListIterator edgeIterator(*edges);
  while (edgeIterator.HasNext()) {
    node_edges = edgeIterator.Next();
    if (node_edges != NULL) {
      NodeEdgeListIterator nodeEdgeIterator(*node_edges);
      while (nodeEdgeIterator.HasNext()) {
        edge = nodeEdgeIterator.Next();
        delete edge;
      }
      delete node_edges;
    }
  }
  delete edges;
}

template <typename TNode, typename TEdge>
inline Graph<TNode,TEdge>::NodeIterator::NodeIterator(const Graph<TNode,TEdge>& graph)
    : position_(0),
      graph_(graph) {}

template <typename TNode, typename TEdge>
inline Graph<TNode,TEdge>::NodeIterator::~NodeIterator() {}

template <typename TNode, typename TEdge>
inline BOOL Graph<TNode,TEdge>::NodeIterator::HasNext() {
  while (position_ < graph_.nodes_->length()) {
    if (graph_.nodes_->Get(position_) != NULL) {
      return true;
    }
    position_++;
  }
  return false;
}

template <typename TNode, typename TEdge>
inline TNode& Graph<TNode,TEdge>::NodeIterator::Next() {
  return *(graph_.nodes_->Get(position_++));
}

template <typename TNode, typename TEdge>
inline Graph<TNode,TEdge>::EdgeIterator::EdgeIterator(const Graph<TNode,TEdge>& graph, I32 index)
    : position_(0),
      graph_(graph) {
  node_edges_ = graph.edges_->Get(index);
}

template <typename TNode, typename TEdge>
inline Graph<TNode,TEdge>::EdgeIterator::~EdgeIterator() {
}

template <typename TNode, typename TEdge>
inline BOOL Graph<TNode,TEdge>::EdgeIterator::HasNext() {
  while (position_ < node_edges_->length()) {
    if (node_edges_->Get(position_) != NULL) {
      return true;
    }
    position_++;
  }
  return false;
}

template <typename TNode, typename TEdge>
inline TEdge& Graph<TNode,TEdge>::EdgeIterator::Next() {
  return *(node_edges_->Get(position_++));
}

}

#endif