#include "unity.h"
#include <unity_fixture.h>

#include <testsrc/add.h>

TEST_GROUP(Add);

TEST_SETUP(Add)
{}

TEST_TEAR_DOWN(Add)
{}

TEST(Add, Add_sample_test){
    TEST_ASSERT_EQUAL_INT(2, Add(1));
}