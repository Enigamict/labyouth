#include "unity.h"
#include <unity_fixture.h>

#include "libstack.h"

TEST_GROUP(stack_pop);

TEST_SETUP(stack_pop)
{}

TEST_TEAR_DOWN(stack_pop)
{}

TEST(stack_pop, pop_test){
    stream_stack *s;
    int data;

    s = stack_init(5);
    stack_push(1, s);
    stack_push(2, s);
    stack_pop(&data, s);
    TEST_ASSERT_EQUAL_INT(2,data);
}
