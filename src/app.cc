#include <stdio.h>
#include <stdlib.h>

#include "shared/list.h"
#include "shared/stack.h"
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

void print(PriorityQueue<int>& queue){
  printf("Priority Queue:\n");
  PriorityQueue<int>::Iterator iterator(queue);
  while (iterator.HasNext()) {
    int item = iterator.Next();
    printf("%i", item);
    printf("\n");
  }
}

}

int main() {
  printf("Dwarf 2015\n");

  Stack<int>* stack = new Stack<int>();

  stack->Push(1);
  stack->Push(2);
  stack->Push(3);
  print(*stack);

  delete stack;

  List<int>* list = new List<int>();

  list->Add(1);
  list->Add(2);
  print(*list);

  delete list;

  PriorityQueue<int>* queue = new PriorityQueue<int>();

  queue->Push(1);
  print(*queue);

  queue->Push(7);
  print(*queue);

  queue->Push(2);
  print(*queue);

  queue->Push(9);
  print(*queue);

  queue->Pop();
  print(*queue);

  queue->Pop();
  print(*queue);

  delete queue;

  exit(0);
}