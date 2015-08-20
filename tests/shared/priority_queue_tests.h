#ifndef DWARF_TESTS_SHARED_PRIORITY_QUEUE_H_
#define DWARF_TESTS_SHARED_PRIORITY_QUEUE_H_

#include <stdio.h>
#include <stdlib.h>

#include "../unit_tests.h"
#include "../../src/shared/priority_queue.h"

namespace dwarf {
namespace tests {
namespace shared {

using namespace dwarf::shared;

void print(PriorityQueue<int>& pqueue) {
#ifdef DEBUG
  printf("Priority Queue: ");
  PriorityQueue<int>::Iterator iterator(pqueue);
  while (iterator.HasNext()) {
    int item = iterator.Next();
    printf("%i ", item);
  }
  printf("\n");
#endif
}

TEST(should_push_items_to_priority_queue) {

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

  ASSERT((pqueue->length() == 2));

  delete pqueue;
}

}
}
}

#endif