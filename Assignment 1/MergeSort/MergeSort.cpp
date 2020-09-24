#include <iostream>
using namespace std;

void Merge(int arr[],int p,int q,int r){
	int *b =new int[r-p+1];
	int i,j;
	for(i = p ; i <= q ; i++){
		b[i-p]=arr[i];
	}
	for(j = r ; j > q ; j--){
		b[i-p]=arr[j];
		i++;
	}
	i = 0;
	j = r-p;
	int k;
	for(k = p ; k < r ; k++){
		if(b[i] < b[j]){
			arr[k] = b[i];
			i++;
		}
		else{
			arr[k] = b[j];
			j--;
		}
	}
	arr[k]=b[j];
}
void MergeSort(int arr[],int p,int r){
        
        if (p < r) { 
            int q = (p + r) / 2; 
  
            MergeSort(arr, p, q); 
            MergeSort(arr, q + 1, r); 
  
            Merge(arr, p, q, r); 
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
    MergeSort(array,0,size-1);
    t1 = clock();

    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    cout << time ;

    return 0;
}
