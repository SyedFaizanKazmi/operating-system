#include <iostream>
#include <pthread.h>
#include <semaphore.h>
using namespace std;
const int buffersize=1;
const int max_item=100;  
sem_t empty_semaphore,full;  
int buffer;
void* producer(void*)
{
for(int i=1;i<=max_item;i++)
{
sem_wait(&empty_semaphore);
buffer = i;
cout<<"produced:"<<i<<endl;
sem_post(&full);
}
return NULL;
}
void* consumer(void*)
{
for(int i=0;i<max_item;i++)
{
sem_wait(&full);
int item=buffer;
cout << "consumed:"<<item<<endl;
sem_post(&empty_semaphore);
}
return NULL;
}
int main()
{
sem_init(&empty_semaphore,0,buffersize);
sem_init(&full,0,0);
pthread_t producer_thread,consumer_thread;
pthread_create(&producer_thread,NULL,producer,NULL);
pthread_create(&consumer_thread,NULL,consumer,NULL);
pthread_join(producer_thread,NULL);
pthread_join(consumer_thread,NULL);
return 0;
}

