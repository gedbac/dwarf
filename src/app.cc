#include <stdio.h>
#include <stdlib.h>

#include "shared/list.h"
#include "shared/stack.h"
#include "shared/queue.h"
#include "shared/comparer.h"
#include "shared/priority_queue.h"

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

  exit(0);
}