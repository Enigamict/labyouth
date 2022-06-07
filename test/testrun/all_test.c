#include <unity_fixture.h>

static void RunAllTests(void)
{
 // RUN_TEST_GROUP(stack_init);
 // RUN_TEST_GROUP(stack_push);
 // RUN_TEST_GROUP(stack_pop);
  RUN_TEST_GROUP(queue_init);
  RUN_TEST_GROUP(queue_enq);
  RUN_TEST_GROUP(queue_deq);
}

int main( int argc, char const **argv )
{
  return UnityMain( argc, argv, RunAllTests );
}