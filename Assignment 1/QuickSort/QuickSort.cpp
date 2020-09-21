#include <iostream>

using namespace std;


void quicksort(int arr[], int izq, int der){//tener en cuenta el orden de los parametros

    int i=izq,j=der,temp;
    int p=arr[(izq+der)/2];
    while(i<=j){
        while(arr[i]<p)i++;
        while(arr[j]>p)j--;
        if(i<=j){
            temp=arr[i];
            arr[i]=arr[j];
            arr[j]=temp;
            i++;
            j--;
        }
    }
      if(izq<j)
            quicksort(arr,izq,i);
      if(i<der)
            quicksort(arr,i,der);

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
    quicksort(array, 0, size -1 );
    t1 = clock();

    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    cout << size << " " << time << endl;

    return 0;
}
