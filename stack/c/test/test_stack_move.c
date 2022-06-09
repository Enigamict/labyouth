#include "unity.h"
#include <unity_fixture.h>

#include "libstack.h"

TEST_GROUP(stack_move);

TEST_SETUP(stack_move)
{}

TEST_TEAR_DOWN(stack_move)
{}

TEST(stack_move, stack_test){
    stream_stack *s;
    const size_t size = 3;
    int data;

    s = stack_init(size);

    for (size_t i = 0; i < size; i++) {
        TEST_ASSERT_TRUE(stack_push(i, s));
    }

    TEST_ASSERT_FALSE(stack_push(3, s));
    stack_print(s);

    for (size_t i = 0; i < size; i++) {
        int data;
        TEST_ASSERT_TRUE(stack_pop(&data, s));
        TEST_ASSERT_EQUAL_INT(size - i - 1, data);
    }

    TEST_ASSERT_FALSE(stack_pop(&data, s));
}
