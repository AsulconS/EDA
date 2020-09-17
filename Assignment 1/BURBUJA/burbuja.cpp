#include <iostream>
#include<cmath>
using namespace std;
void bu(int arr[], int n){
    int temp;
    for (int i=0;i<n;i++){
        for(int e=0;e<n-1;e++){
            if(arr[e]>arr[e+1]){
                temp=arr[e];
                arr[e]=arr[e+1];
                arr[e+1]=temp;
            }
        }
    }
}


int main(){
    int cantidad;
    cin>>cantidad;
    int arr[cantidad]={};
    int num;
    srand(time(NULL));
    for (int i = 0; i < cantidad; i++)
    {
        num = 1+ rand() % (cantidad-1);
        arr[i] = num;
    }

    unsigned t0, t1;

    t0 = clock();
    bu(arr, cantidad);
    t1 = clock();

    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    cout<<cantidad<<" "<<time<<endl;
    
}