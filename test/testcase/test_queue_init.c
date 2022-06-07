#include "unity.h"
#include <unity_fixture.h>

#include "libqueue.h"

TEST_GROUP(queue_init);

TEST_SETUP(queue_init)
{}

TEST_TEAR_DOWN(queue_init)
{}

TEST(queue_init, max_test) {

    TEST_ASSERT_NULL(queue_init(4294967295));
}
