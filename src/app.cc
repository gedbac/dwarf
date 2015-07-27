#include <stdio.h>
#include <stdlib.h>

#include "shared/comparer.h"
#include "shared/priority_queue.h"

using namespace dwarf::shared;

void print(PriorityQueue<int>& queue){
  printf("Priority Queue:\n");
  PriorityQueue<int>::Iterator pqueueIterator(queue);
  while (pqueueIterator.HasNext()) {
    int item = pqueueIterator.Next();
    printf("%i", item);
    printf("\n");
  }
}

int main() {
  printf("Dwarf 2015\n");

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