#ifndef DWARF_TESTS_SHARED_QUEUE_H_
#define DWARF_TESTS_SHARED_QUEUE_H_

#include <stdio.h>
#include <stdlib.h>

#include "../unit_tests.h"
#include "../../src/shared/queue.h"

namespace dwarf {
namespace tests {
namespace shared {

using namespace dwarf::shared;

void print(Queue<int>& queue) {
#ifdef DEBUG
  printf("Queue: ");
  Queue<int>::Iterator iterator(queue);
  while (iterator.HasNext()) {
    int item = iterator.Next();
    printf("%i ", item);
  }
  printf("\n");
#endif
}

TEST(should_push_items_to_queue) {

  Queue<int>* queue = new Queue<int>();

  queue->Push(1);
  queue->Push(2);
  queue->Push(3);
  print(*queue);

  ASSERT((queue->length() == 3));

  delete queue;

}

}
}
}

#endif