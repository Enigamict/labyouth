#include "unity.h"
#include <unity_fixture.h>

#include "libqueue.h"

TEST_GROUP(queue_enq);

TEST_SETUP(queue_enq)
{}

TEST_TEAR_DOWN(queue_enq)
{}

TEST(queue_enq, enq_test){
    stream_queue *q;
    int data;
    
    q = queue_init(5);
    TEST_ASSERT_TRUE(queue_enqueue(q, 1));
    TEST_ASSERT_TRUE(queue_enqueue(q, 2));
    TEST_ASSERT_TRUE(queue_enqueue(q, 3));
    TEST_ASSERT_TRUE(queue_enqueue(q, 4));
    TEST_ASSERT_TRUE(queue_enqueue(q, 5));
    printf("enqueue test\n");
    queue_print(q);
    queue_dequeue(q, &data);
    printf("dequeue value :%d\n", data);
    queue_print(q);
    printf("ring buffer enqueue add 6\n");
    TEST_ASSERT_TRUE(queue_enqueue(q, 6));
    queue_print(q);
}
