#include<iostream>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
using namespace std;
void merge(int arr[], int p, int q, int r) 
{
int n1 = q - p + 1;
int n2 = r - q;
int subarr1[n1], subarr2[n2];
for(int i = 0; i < n1; i++)
{
subarr1[i] = arr[p + i];
}
for(int j = 0; j < n2; j++)
{
subarr2[j] = arr[q + 1 + j];
}
int i = 0, j = 0, k = p;
while(i < n1 && j < n2) 
{
if (subarr1[i] <= subarr2[j]) 
{
arr[k] = subarr1[i];
i++;
}
else 
{
arr[k] = subarr2[j];
j++;
}
k++;
}
while (i < n1) 
{
arr[k] = subarr1[i];
i++;
k++;
}
while (j < n2) 
{
arr[k] = subarr2[j];
j++;
k++;
}
}
 
void mergesort(int arr[], int startindex, int endiindex) {
if(startindex < endiindex) 
{
int mid = startindex + (endiindex - startindex) / 2;
mergesort(arr, startindex, mid);
mergesort(arr, mid + 1, endiindex);
merge(arr, startindex, mid, endiindex);
}
}
int main() 
{
int arr[]={7,5,10,18,8,6,9,11,2,3,1,4};
int size =sizeof(arr)/sizeof(arr[0]);
int s=size-1;
pid_t pid;
pid=fork();
if(pid == -1) {
cout<<"fork not made.";
return 1;
} 
else if(pid == 0) 
{
mergesort(arr,0,s/2);
} 
else 
{
mergesort(arr,0,s/2);
mergesort(arr,s/2+1,s);
wait(NULL);
merge(arr,0,s/2,s);
for(int i=0;i<=s;i++)
    cout<<arr[i]<<" ";
}
return 0;
}