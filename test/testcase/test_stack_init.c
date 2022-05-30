#include "unity.h"
#include <unity_fixture.h>

#include <stack/libstack.h>

TEST_GROUP(stack_init);

TEST_SETUP(stack_init)
{}

TEST_TEAR_DOWN(stack_init)
{}

TEST(stack_init, max_test){
    stream_stack s;
    memset(&s, 0, sizeof(s));

    TEST_ASSERT_NOT_NULL(stack_init(&s, 1410065408));
}

TEST(stack_init, minus_test){
    stream_stack s;
    memset(&s, 0, sizeof(s));

    TEST_ASSERT_NOT_NULL(stack_init(&s, -1));
}