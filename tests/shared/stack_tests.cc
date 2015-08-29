#include <stdio.h>
#include <stdlib.h>

#include "unit_tests.h"
#include "stack.h"

using namespace dwarf;

void print(Stack<I32>& stack) {
#ifdef DEBUG
  printf("Stack: ");
  Stack<I32>::Iterator iterator(stack);
  while (iterator.HasNext()) {
    int item = iterator.Next();
    printf("%i ", item);
  }
  printf("\n");
#endif
}

TEST(should_push_items_to_stack) {

  Stack<I32>* stack = new Stack<I32>();

  stack->Push(1);
  stack->Push(2);
  stack->Push(3);
  print(*stack);

  ASSERT((stack->length() == 3));

  delete stack;

}