#include <iostream>
#include <cstdlib>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
using namespace std;

int main(int argc, char** argv)
{
    cout<<"\n \n \t \t \t Welcome to my shell";
    while (1) {
        char str[100];
        cout << "\n \t \t \t >>>";
        cin.getline(str, 100);

        int j = 0; 
        char* token = strtok(str, " ");
        char* command[100]; 
        
        while (token != NULL)
        {
            command[j] = token;
            j++;
            token = strtok(NULL, " ");
        }
        
        if (j == 0) {
            continue;
        }
        command[j] = NULL;

        if (strcmp(command[0], "exit") == 0) {
            cout << "\n \t \t \t Thank you for using my shell \n" << endl;
            break;
        } else if (strcmp(command[0], "cd") == 0) {
            if (j < 2) {
                cout << "Usage: cd <directory>" << endl;
            } else {
                if (chdir(command[1]) != 0) {
                    cout << "Failed to change directory" << endl;
                }
            }
        } else {
            int pid = fork();
            if (pid == 0) {
                execvp(command[0], command);
                cout << "Failed to execute your command" << endl;
                exit(1);
            } else if (pid > 0) {
                wait(NULL);
            } else {
                cout << "Can't create a child process" << endl;
            }
        }
    }

    return 0;
}
