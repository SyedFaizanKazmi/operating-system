#include <iostream>
#include <semaphore.h>
#include <thread>
using namespace std;
const int total_philosopers=5;
pthread_t philosopers[total_philosopers];
sem_t sem[total_philosopers];
void philosopher(void* arg)
{
int id=*((int*)arg);
int left_fork=id;
int right_fork=(id+1)%total_philosopers;
while(true)
{
cout<<"philosoper no: "<<id<<" is thinking"<<endl;
this_thread::sleep_for(chrono::seconds(1));
sem_wait(&sem[left_fork]);
cout<<"philosoper "<<id<<" picked up the left fork."<<endl;
sem_wait(&sem[right_fork]);
cout<<"philosopher "<<id<<" picked up the right fork and started eating."<<endl;
this_thread::sleep_for(chrono::seconds(1));
sem_post(&sem[left_fork]);
sem_post(&sem[right_fork]);
cout<<"philosopher "<<id<<" has finished eating and release both forks."<<endl;
}
}
int main()
{
for(int i=0;i<total_philosopers;i++)
{
sem_init(&sem[i],0,1);
}
int philosopher_id[total_philosopers];
for(int i=0;i<total_philosopers;i++)
{
philosopher_id[i]=i+1;
pthread_create(&philosopers[i],NULL,(void*(*)(void*))philosopher,&philosopher_id[i]);
}
for (int i = 0; i < total_philosopers; ++i) {
pthread_join(philosopers[i],NULL);
sem_destroy(&sem[i]);
}
return 0;
}

