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
    int arr[]= {0,1,2,3,4,5,6,7};
    MergeSort(arr,0,7);
    for (int i = 0; i < 8; i++)
    {
        cout << arr[i] << " ";
    }
    
        
}
