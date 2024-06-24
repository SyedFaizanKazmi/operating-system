#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <vector>
using namespace std;

void deposit(int acc, int amount, vector<int>& acc_bal) 
{
acc_bal[acc] += amount;
cout << "deposited $" << amount << "in account " << acc << "balance is: $" << acc_bal[acc] << endl;
}

void withdraw(int acc, int amount, vector<int>& acc_bal) {
if (acc_bal[acc] >= amount) {
acc_bal[acc] -= amount;
cout << "Withdrawn $" << amount << "in account " << acc << "balance is: $" << acc_bal[acc] << endl;
}
else { cout << "insufficient funds in account " << acc << ". Balance: $" << acc_bal[acc] << endl;
    }
}

int main() {
 int numofacc = 3;
 int ini_bal = 0;
vector<int> acc_balance(numofacc, ini_bal);
pid_t pid;
int deposits, credits;
 for (int i = 0; i < numofacc; i++) {
        pid = fork();
 if (pid == -1) {
            cout << "fork not made.";
            return 1;
 }
        else if (pid == 0) {
   cout << "child " << i << " - Account " << i << " balance: $" << acc_balance[i] << endl;
 cout << "child " << i << " - Enter amount to deposit: ";
            cin >> deposits;
            deposit(i, deposits, acc_balance);
            cout << "child " << i << " - Enter amount to credit: ";
            cin >> credits;
            withdraw(i, credits, acc_balance);
            exit(0);
        }
    }
 for (int i = 0; i < numofacc; i++) {
        wait(NULL);
    }
  return 0;
}
