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
    
    int input,size;
    cin >> size;
    int array[size];
    for(int i = 0 ; i < size ; i++ )
    {
        cin >> input;
        array[i] = input;
    }
    
    unsigned t0,t1;

    t0 = clock();
    bu(array, size);
    t1 = clock();

    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    cout << time ;

    return 0;

}
