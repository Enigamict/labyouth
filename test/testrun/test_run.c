#include "unity.h"
#include <unity_fixture.h>

TEST_GROUP_RUNNER(stack_init) {
    RUN_TEST_CASE(stack_init, max_test);
    RUN_TEST_CASE(stack_init, minus_test);
}

TEST_GROUP_RUNNER(stack_push) {
    RUN_TEST_CASE(stack_push, push_test);
    RUN_TEST_CASE(stack_push, over_push_test);
}

TEST_GROUP_RUNNER(stack_pop) {
    RUN_TEST_CASE(stack_pop, pop_test);
}