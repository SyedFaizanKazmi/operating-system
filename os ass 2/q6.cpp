#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;
int main() {
int cookcount = 2;
int c_count = 3;
int orders = 5;
int totalorders = 0;
int c_to_w[2];
int w_to_c[2];
pipe(c_to_w);
pipe(w_to_c);
for (int i = 0; i < cookcount; i++) 
{
pid_t cpid = fork();
if (cpid == -1)
{
cout << "fork not created";
return 1;
}
else if (cpid == 0) 
{
 close(c_to_w[0]);  
 close(w_to_c[1]);  
 while (totalorders < c_count * orders) 
 {
 int order;
 read(w_to_c[0], &order, sizeof(order));
 cout << "cook " << i << ": Received order " << order << endl;
  cout << "Cook " << i << ": Preparing food for order " << order << endl;
  write(c_to_w[1], &order, sizeof(order));
  cout << "Cook " << i << ": Sent food to the order number: " << order << " to the waiter" << endl;
  totalorders++;
  }
   close(c_to_w[1]); 
 close(w_to_c[0]); 
 exit(0);
 } }
 for (int i = 0; i < c_count; i++) {
 pid_t cu_pid = fork();
 if (cu_pid == -1) {
 cout << "fork not created";
 return 1;
 } else if (cu_pid == 0) 
 { 
 close(c_to_w[1]);  
 close(w_to_c[0]);  
 for (int j = 0; j < orders; j++) 
 { 
 int order = i * orders + j + 1;
  cout << "Customer " << i << ": Placing order number: " << order << std::endl;
 write(w_to_c[1], &order, sizeof(order));
 read(c_to_w[0], &order, sizeof(order));
  cout << "Customer " << i << ": Received food for the order number " << order << endl;
            }
 close(c_to_w[0]);  
 close(w_to_c[1]);  
 exit(0);
  }
 }
 for (int i = 0; i < cookcount + c_count; i++) 
 {
 wait(NULL);
  }
  cout<<"BYE BYE !!";
 return 0;
}
