#include "unity.h"
#include <unity_fixture.h>

#include "libstack.h"

TEST_GROUP(stack_init);

TEST_SETUP(stack_init)
{}

TEST_TEAR_DOWN(stack_init)
{}

TEST(stack_init, max_test) {

    TEST_ASSERT_NULL(stack_init(4294967295));
}
