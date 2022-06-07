#include "unity.h"
#include <unity_fixture.h>

TEST_GROUP_RUNNER(queue_init) {
    RUN_TEST_CASE(queue_init, max_test);
}

TEST_GROUP_RUNNER(queue_enq) {
    RUN_TEST_CASE(queue_enq, enq_test);
}

TEST_GROUP_RUNNER(queue_deq) {
    RUN_TEST_CASE(queue_deq, deq_test);
}