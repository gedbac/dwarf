#include <stdio.h>
#include <stdlib.h>

#include "unit_tests.h"
#include "queue.h"

using namespace dwarf;

void print(Queue<I32>& queue) {
#ifdef DEBUG
  printf("Queue: ");
  Queue<I32>::Iterator iterator(queue);
  while (iterator.HasNext()) {
    int item = iterator.Next();
    printf("%i ", item);
  }
  printf("\n");
#endif
}

TEST(should_push_items_to_queue) {

  Queue<I32>* queue = new Queue<I32>();

  queue->Push(1);
  queue->Push(2);
  queue->Push(3);
  print(*queue);

  ASSERT((queue->length() == 3));

  delete queue;

}