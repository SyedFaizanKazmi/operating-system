#include<iostream>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
using namespace std;
int isPrime(int n)
{
if(n <= 1) 
{
return 0; 
}
for(int i = 2; i*i <= n; i++)
{
if(n%i == 0)
{
return 0;
}}
return 1;
}
int main() 
{
int n1,n2;
cout<<"enter starting range: ";
cin>>n1;
cout<<"enter ending range: ";
cin>>n2;
pid_t pid;
pid = fork();
if(pid == -1) {
cout<<"fork not made.";
return 1;
} 
else if(pid == 0) 
{
cout<<"the prime numbers b/w "<<n1<<" and "<<n2<<" :"<<endl;
for(int i = n1; i <= n2; i++)
{
if(isPrime(i))
{
cout<<i<<" ";
} 
}}
else 
{
wait(NULL);
}
return 0;
}