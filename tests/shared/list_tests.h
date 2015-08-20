#ifndef DWARF_TESTS_SHARED_LIST_H_
#define DWARF_TESTS_SHARED_LIST_H_

#include <stdio.h>
#include <stdlib.h>

#include "../unit_tests.h"
#include "../../src/shared/list.h"

namespace dwarf {
namespace tests {
namespace shared {

using namespace dwarf::shared;

void print(List<int>& list) {
#ifdef DEBUG
  printf("List: ");
  List<int>::Iterator iterator(list);
  while (iterator.HasNext()) {
    int item = iterator.Next();
    printf("%i ", item);
  }
  printf("\n");
#endif
}

TEST(should_add_items_to_list) {

  List<int>* list = new List<int>();

  list->Add(1);
  list->Add(2);

  print(*list);

  ASSERT((list->length() == 2));

  delete list;

}

}
}
}

#endif