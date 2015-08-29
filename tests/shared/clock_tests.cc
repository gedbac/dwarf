#include "unit_tests.h"
#include "clock.h"

using namespace dwarf;

TEST(should_get_current_time) {
  Clock clock;
  clock.Start();
  I64 current_time = clock.GetCurrentTime();
  ASSERT((current_time > 0));
}