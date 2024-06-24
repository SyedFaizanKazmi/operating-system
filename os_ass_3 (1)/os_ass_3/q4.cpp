#include <iostream>
#include <thread>
#include <mutex>
#include <semaphore.h>
using namespace std;
mutex mtx;
sem_t sem;
int global_counter = 0;
const int no_of_iteration = 100;
void thread_function1()
{
for(int i=0;i<no_of_iteration;i++)
{
sem_wait(&sem);
lock_guard<mutex> lock(mtx);
global_counter++;
cout<<"thread 1: iteration no: "<<i+1<<",\tTotal count: "<<global_counter<<endl;
sem_post(&sem);
}
}
void thread_function2()
{
for(int i=0;i<no_of_iteration;i++)
{
sem_wait(&sem); 
lock_guard<mutex>lock(mtx);
global_counter++;
cout<<"thread 2: iteration no: "<<i+1<<",\tTotal count: "<<global_counter<<endl;
sem_post(&sem); 
}
}
int main()
{
sem_init(&sem,0,1);
thread t1(thread_function1);
thread t2(thread_function2);
t1.join();
t2.join();
cout<<"final count: "<<global_counter<<endl;
sem_destroy(&sem);
return 0;
}

