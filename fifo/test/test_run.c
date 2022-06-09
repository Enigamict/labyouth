#include "unity.h"
#include <unity_fixture.h>

TEST_GROUP_RUNNER(queue_init) {
    RUN_TEST_CASE(queue_init, max_test);
}

TEST_GROUP_RUNNER(queue_move) {
    RUN_TEST_CASE(queue_move, queue_test);
}

