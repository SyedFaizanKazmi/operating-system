#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;
int main()
{
int num, sqrtnum;
cout << "Enter a number: ";
cin >> num;
int pipee[2];
if (pipe(pipee) == -1) {
 cout << "pipe not created";
 return 1;
 }
pid_t pid = fork();
if (pid == -1) {
 cout << "fork not created";
 return 1;
    }
if (pid == 0) {
 close(pipee[0]);  
 int square = num * num;
 write(pipee[1], &square, sizeof(square));  // Send the square to the parent
close(pipee[1]);
 exit(0);
    }
else 
{
 close(pipee[1]);
 read(pipee[0], &sqrtnum, sizeof(sqrtnum));  
close(pipee[0]);
cout << "The square of " << num << " is: " << sqrtnum << endl;
wait(NULL);
    }
    return 0;
}
