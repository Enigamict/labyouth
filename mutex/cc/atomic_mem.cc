#include <iostream>
#include <atomic>
#include <thread>

int x;
int y;

std::atomic<int> a(0);

void f()
{

  x = 1;
  int r1 = y;
  std::cout << r1 << std::endl;
  std::atomic_thread_fence(std::memory_order_release);    // a2
  a.store(1, std::memory_order_relaxed);                  // a3
}

void f1()
{
  while(a.load(std::memory_order_relaxed) != 1);         // b1
  std::atomic_thread_fence(std::memory_order_acquire);    // b2
  y = 1;
  int r2 = x;
  std::cout << r2 << std::endl;
}

int main()
{
  std::thread t(f);
  std::thread t1(f1);

  t.join();
  t1.join();

  std::cout << "fence?"<< x << std::endl;
  std::cout << "fence?"<< y << std::endl;
  std::cout << "fence?"<< a << std::endl;
}