#include <iostream>
#include <thread>
#include <mutex>
using namespace std;
const int N=10;
int thread_counter=1;
mutex print_fib;
int fac(int n)
{
if(n<=1)
{
return 1;
}
return n*fac(n-1);
}
void cal_print(int thread_no)
{
int ans=fac(thread_no);
while(true)
{
lock_guard<mutex> lock(print_fib);
if(thread_no==thread_counter)
{
cout<<"thread "<<thread_no << ":"<<ans<<endl;
thread_counter++;
break;
}
}
}
int main()
{
thread threads[N];
for(int i=1;i<=N;i++)
{
threads[i-1] =thread(cal_print,i);
}
for(int i=0;i<N;i++) 
{
threads[i].join();
}
return 0;
}

