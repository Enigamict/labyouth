#include "unity.h"
#include <unity_fixture.h>

#include "libqueue.h"

TEST_GROUP(queue_move);

TEST_SETUP(queue_move)
{}

TEST_TEAR_DOWN(queue_move)
{}

TEST(queue_move, queue_test){
    stream_queue *q;
    
    q = queue_init(3);
    queue_enqueue(q, 3);
    queue_enqueue(q, 4);

    for (int i = 5; i < 100; i++) {
        int data;
        queue_print(q);
        queue_enqueue(q, i);
        queue_dequeue(q, &data);
        TEST_ASSERT_EQUAL_INT(i - 2, data);
    }
}