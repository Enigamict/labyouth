#include <unity_fixture.h>

static void RunAllTests(void)
{
  RUN_TEST_GROUP(Add);
}

int main( int argc, char const **argv )
{
  return UnityMain( argc, argv, RunAllTests );
}