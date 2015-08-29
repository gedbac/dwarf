#include <stdio.h>
#include <stdlib.h>

#include "unit_tests.h"
#include "list.h"

using namespace dwarf;

void print(List<I32>& list) {
#ifdef DEBUG
  printf("List: ");
  List<I32>::Iterator iterator(list);
  while (iterator.HasNext()) {
    int item = iterator.Next();
    printf("%i ", item);
  }
  printf("\n");
#endif
}

TEST(should_add_items_to_list) {

  List<I32>* list = new List<I32>();

  list->Add(1);
  list->Add(2);

  print(*list);

  ASSERT((list->length() == 2));

  delete list;

}