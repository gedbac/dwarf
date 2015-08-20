#ifndef UNIT_TESTS_H_
#define UNIT_TESTS_H_

#include <stdio.h>
#include <stdlib.h>
#include <vector>

#define TT_COLOR_CODE 0x1B
#define TT_COLOR_RED "[1;31m"
#define TT_COLOR_GREEN "[1;32m"
#define TT_COLOR_RESET "[0m"

#define TEST(name) \
  void name(); \
  TestRegistration t_##name (Test(#name, &name)); \
  void name()

#define SKIP_TEST(name) \
  void name()

typedef void(*TestFunc)();

struct Test {
  const char* name;
  TestFunc func;
  Test(const char* name, TestFunc func)
    : name(name),
      func(func) {}
};

std::vector<Test> tests;

struct TestRegistration {
  TestRegistration(const Test& test) {
    tests.push_back(test);
  }
};

const char* current_test_name = NULL;

void run_all_tests() {
  for (std::vector<Test>::iterator test = tests.begin(); test != tests.end(); ++test) {
    current_test_name = test->name;
    test->func();
    printf("%c%sPASSED%c%s %s\n", TT_COLOR_CODE, TT_COLOR_GREEN, TT_COLOR_CODE, TT_COLOR_RESET, current_test_name);
  }
}

#define ASSERT(expression) \
  if (!expression) { \
    printf("%c%sFAILED%c%s %s\n", TT_COLOR_CODE, TT_COLOR_RED, TT_COLOR_CODE, TT_COLOR_RESET, current_test_name); \
    printf("%c%s  assertion failed: (%s) has failed in file %s at line %d%c%s\n", TT_COLOR_CODE, TT_COLOR_RED, #expression, __FILE__, __LINE__, TT_COLOR_CODE, TT_COLOR_RESET); \
    exit(1); \
  }

#endif