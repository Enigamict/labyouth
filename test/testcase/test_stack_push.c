#include "unity.h"
#include <unity_fixture.h>

#include <stack/libstack.h>

TEST_GROUP(stack_push);

TEST_SETUP(stack_push)
{}

TEST_TEAR_DOWN(stack_push)
{}

TEST(stack_push, push_test){
    stream_stack s;

    memset(&s, 0, sizeof(s));
    stack_init(&s, 5);

    TEST_ASSERT_TRUE(stack_push(1, &s));
    stack_print(&s);
}

TEST(stack_push, over_push_test){
    stream_stack s;

    memset(&s, 0, sizeof(s));
    stack_init(&s, 5);

    TEST_ASSERT_TRUE(stack_push(1, &s));
    TEST_ASSERT_TRUE(stack_push(1, &s));
    TEST_ASSERT_TRUE(stack_push(1, &s));
    TEST_ASSERT_TRUE(stack_push(1, &s));
    TEST_ASSERT_TRUE(stack_push(1, &s));
    TEST_ASSERT_TRUE(stack_push(1, &s));
    stack_print(&s);
}
