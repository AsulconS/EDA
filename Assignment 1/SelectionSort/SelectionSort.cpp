#include <iostream>
#include <ctime>
using namespace std;

void selectionSort(int *arr,int size)
{
    int temp;
    for(int i = 0 ; i < size - 1 ;  i++ )
    {
        int minimo = i;
        for ( int j = i+1 ; j < size  ;  j++ )
        {
            if( arr[minimo] > arr[j] )
                minimo = j ;
        }

        temp = arr[i];
        arr[i] = arr[minimo];
        arr[minimo] = temp;
        
    }
}



int main()
{
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
    selectionSort(array,size);
    t1 = clock();

    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    cout << time << endl;

    return 0;
}
