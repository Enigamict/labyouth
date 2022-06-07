#include "unity.h"
#include <unity_fixture.h>

#include "libqueue.h"

TEST_GROUP(queue_deq);

TEST_SETUP(queue_deq)
{}

TEST_TEAR_DOWN(queue_deq)
{}

TEST(queue_deq, deq_test){
    stream_queue *q;
    int data;
    
    q = queue_init(5);
    TEST_ASSERT_TRUE(queue_enqueue(q, 1));
    TEST_ASSERT_TRUE(queue_enqueue(q, 2));
    TEST_ASSERT_TRUE(queue_enqueue(q, 3));
    TEST_ASSERT_TRUE(queue_enqueue(q, 4));
    TEST_ASSERT_TRUE(queue_enqueue(q, 5));
    printf("dequeue test\n");
    queue_print(q);
    TEST_ASSERT_TRUE(queue_dequeue(q, &data));
    printf("dequeue value: %d\n", data);
    queue_print(q);
}