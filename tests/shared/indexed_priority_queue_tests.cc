#include <stdio.h>
#include <stdlib.h>

#include "unit_tests.h"
#include "indexed_priority_queue.h"

using namespace dwarf;

void print(IndexedPriorityQueue<double>& queue) {
#ifdef DEBUG
  printf("Indexed Priority Queue: ");
  IndexedPriorityQueue<double>::Iterator iterator(queue);
  while (iterator.HasNext()) {
    int item = iterator.Next();
    printf("%i ", item);
  }
  printf("\n");
#endif
}

TEST(should_push_items_to_indexed_priority_queue) {

  IndexedPriorityQueue<double>* ipq = new IndexedPriorityQueue<double>(Comparer<double>(true));

  int index = -1;

  ipq->Push(4, 4.0);
  print(*ipq);

  ipq->Push(1, 1.0);
  print(*ipq);

  ipq->Push(5, 5.0);
  print(*ipq);

  ipq->Push(2, 2.0);
  print(*ipq);

  index = ipq->Pop();
  print(*ipq);
  ASSERT((index == 5));

  index = ipq->Pop();
  print(*ipq);
  ASSERT((index == 4));

  ASSERT((ipq->length() == 2));

  delete ipq;

}