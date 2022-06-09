#include "unity.h"
#include <unity_fixture.h>

TEST_GROUP_RUNNER(stack_init) {
    RUN_TEST_CASE(stack_init, max_test);
}

TEST_GROUP_RUNNER(stack_move) {
    RUN_TEST_CASE(stack_move, stack_test);
}
