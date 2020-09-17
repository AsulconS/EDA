#include <iostream>
#include <time.h>
using namespace std;

void insertion(int arr[],   int tam){
    int aux, pos;
    for (int i=0;i<tam;i++){
        pos=i;//guarda la posicion
        aux=arr[i];//numero del arreglo
        while((pos>0)&&(arr[pos-1]>aux)){
            arr[pos]=arr[pos-1];
            pos--;//iteraciones hacia atras
        }
        arr[pos]=aux;
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
    insertion(arr, cantidad);
    t1 = clock();

    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    cout<<cantidad<<" "<<time<<endl;
    
}