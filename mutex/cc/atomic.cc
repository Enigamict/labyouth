#include <atomic>
#include <iostream>
#include <thread>

int r1;
int r2;

int r3;
int r4;
std::atomic<int> a(0), b(0);

void thread1() {
    a.store(1, std::memory_order_release);                  
}

void thread2() {
    b.store(1, std::memory_order_release);
}

void thread3() {
    r1 = a.load(std::memory_order_seq_cst);
    r2 = b.load(std::memory_order_seq_cst);
    std::cout << "r1 : " << r1 << std::endl;
    std::cout << "r2 : " << r2 << std::endl;
}

void thread4() {
    r3 = b.load(std::memory_order_seq_cst);
    r4 = a.load(std::memory_order_seq_cst);
    std::cout << "r3 : " << r3 << std::endl;
    std::cout << "r4 : " << r4 << std::endl;
}

int main() {
    std::thread t1(thread1);
    std::thread t2(thread2);
    std::thread t3(thread3);
    std::thread t4(thread4);

    t1.join();
    t2.join();
    t3.join();
    t4.join();


    return 0;
}