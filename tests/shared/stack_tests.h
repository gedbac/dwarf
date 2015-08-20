#ifndef DWARF_TESTS_SHARED_STACK_H_
#define DWARF_TESTS_SHARED_STACK_H_

#include <stdio.h>
#include <stdlib.h>

#include "../unit_tests.h"
#include "../../src/shared/stack.h"

namespace dwarf {
namespace tests {
namespace shared {

using namespace dwarf::shared;

void print(Stack<int>& stack) {
#ifdef DEBUG
  printf("Stack: ");
  Stack<int>::Iterator iterator(stack);
  while (iterator.HasNext()) {
    int item = iterator.Next();
    printf("%i ", item);
  }
  printf("\n");
#endif
}

TEST(should_push_items_to_stack) {

  Stack<int>* stack = new Stack<int>();

  stack->Push(1);
  stack->Push(2);
  stack->Push(3);
  print(*stack);

  ASSERT((stack->length() == 3));

  delete stack;

}

}
}
}

#endif