#include <iostream>

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
    int arr[] = { 10 ,9 ,8 ,7 , 6,5 ,4, 3, 2, 1};
    selectionSort(arr,10);
    for (int i = 0 ; i < 10 ; i++ )
         cout << arr[i] << " ";
    return 0;
}
