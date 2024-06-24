#include<iostream>
#include<unistd.h>
#include<sys/types.h>
using namespace std;
int main() 
{
pid_t pid;
pid=fork();
if(pid == -1) {
cout<<"fork not made.";
return 1;
} 
else if(pid == 0) 
{
cout<<"child process displaying its process ID (PID): "<<getpid()<<endl;
} 
else 
{
cout<<"parent process displaying the PID of the child: "<<pid<<endl;
}
return 0;
}
