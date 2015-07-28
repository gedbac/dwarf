#include <stdio.h>
#include <stdlib.h>

#include "shared/list.h"
#include "shared/stack.h"
#include "shared/queue.h"
#include "shared/comparer.h"
#include "shared/priority_queue.h"
#include "shared/graph_node.h"
#include "shared/graph_edge.h"
#include "shared/graph.h"

namespace {

using namespace dwarf::shared;

void print(List<int>& list) {
  printf("List:\n");
  List<int>::Iterator iterator(list);
  while (iterator.HasNext()) {
    int item = iterator.Next();
    printf("%i", item);
    printf("\n");
  }
}

void print(Stack<int>& stack) {
  printf("Stack:\n");
  Stack<int>::Iterator iterator(stack);
  while (iterator.HasNext()) {
    int item = iterator.Next();
    printf("%i", item);
    printf("\n");
  }
}

void print(PriorityQueue<int>& queue) {
  printf("Priority Queue:\n");
  PriorityQueue<int>::Iterator iterator(queue);
  while (iterator.HasNext()) {
    int item = iterator.Next();
    printf("%i", item);
    printf("\n");
  }
}

void print(Queue<int>& queue) {
  printf("Queue:\n");
  Queue<int>::Iterator iterator(queue);
  while (iterator.HasNext()) {
    int item = iterator.Next();
    printf("%i", item);
    printf("\n");
  }
}

void print(Graph<GraphNode, GraphEdge>& graph) {
  printf("Graph:\n");
  Graph<GraphNode, GraphEdge>::NodeIterator nodeIterator(graph);
  while (nodeIterator.HasNext()) {
    GraphNode& node = nodeIterator.Next();
    printf("%i", node.index());
    Graph<GraphNode, GraphEdge>::EdgeIterator edgeIterator(graph, node.index());
    while (edgeIterator.HasNext()) {
      GraphEdge& edge = edgeIterator.Next();
      printf("->%i", edge.to());
    }
    printf("\n");
  }
  printf("Nodes: %i Edges: %i \n", graph.NodeCount(), graph.EdgeCount());
}

}

int main() {

  printf("Dwarf 2015\n");

  List<int>* list = new List<int>();

  list->Add(1);
  list->Add(2);
  print(*list);

  delete list;

  Stack<int>* stack = new Stack<int>();

  stack->Push(1);
  stack->Push(2);
  stack->Push(3);
  print(*stack);

  delete stack;

  Queue<int>* queue = new Queue<int>();

  queue->Push(1);
  queue->Push(2);
  queue->Push(3);
  print(*queue);

  delete queue;

  PriorityQueue<int>* pqueue = new PriorityQueue<int>();

  pqueue->Push(1);
  print(*pqueue);

  pqueue->Push(7);
  print(*pqueue);

  pqueue->Push(2);
  print(*pqueue);

  pqueue->Push(9);
  print(*pqueue);

  pqueue->Pop();
  print(*pqueue);

  pqueue->Pop();
  print(*pqueue);

  delete pqueue;

  Graph<GraphNode,GraphEdge>* graph = new Graph<GraphNode,GraphEdge>();

  graph->CreateNode(0);
  graph->CreateNode(1);
  graph->CreateNode(2);
  graph->CreateNode(3);
  graph->CreateNode(4);
  graph->CreateNode(5);
  graph->CreateEdge(0, 1);
  graph->CreateEdge(0, 2);
  graph->CreateEdge(1, 4);
  graph->CreateEdge(2, 3);
  graph->CreateEdge(3, 4);
  graph->CreateEdge(3, 5);
  graph->CreateEdge(4, 5);

  print(*graph);

  delete graph;

  exit(0);
}