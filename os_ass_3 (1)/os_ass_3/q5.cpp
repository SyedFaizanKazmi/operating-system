#include <iostream>
#include <pthread.h>
#include <semaphore.h>
using namespace std;
sem_t bank;
int bal=1000;
void* update(void* arg)
{
int thread_id=*((int*)arg);
for (int i = 0; i < 5; i++) 
{
sem_wait(&bank);
bal-= 200;
cout<<"thread " << thread_id << " updated the balance to: $"<<bal<<endl;
sem_post(&bank);
}
return NULL;
}
int main()
{
sem_init(&bank,0,1);
cout<<"initial balance: $"<<bal<<endl;
pthread_t threadA,threadB,threadC;
int A=1,B=2,C=3;
pthread_create(&threadA,NULL,update,&A);
pthread_create(&threadB,NULL,update,&B);
pthread_create(&threadC,NULL,update,&C);
pthread_join(threadA,NULL);
pthread_join(threadB,NULL);
pthread_join(threadC,NULL);
cout<<"total final balance: $"<<bal<<endl;
return 0;
}

