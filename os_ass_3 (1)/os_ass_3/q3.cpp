#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>
using namespace std;
sem_t sem_A, sem_B, sem_C;
void printA()
{
for(int i=0;i<10;i++)
{
sem_wait(&sem_A);
for(int j=0;j<3;j++)
{
cout << "a";
}
sem_post(&sem_C);
}
}
void printB()
{
for(int i=0;i<10;i++)
{
sem_wait(&sem_B);
cout << "b";
sem_post(&sem_A);
}
}
void printC()
{
for(int i=0;i<10;i++)
{
sem_wait(&sem_C);
cout << "c";
sem_post(&sem_B);
}
}
int main()
{
sem_init(&sem_A,1,1);  
sem_init(&sem_B,1,0);  
sem_init(&sem_C,1,0);  
pid_t child1,child2,child3;
child1=fork();
if(child1==0)
{
printA();
}
child2=fork();
if(child2==0)
{
printB();
}
child3 = fork();
if(child3==0)
{
printC();
}
waitpid(child1,NULL,0);
waitpid(child2,NULL,0);
waitpid(child3,NULL,0);
sem_destroy(&sem_A);
sem_destroy(&sem_B);
sem_destroy(&sem_C);
return 0;
}

