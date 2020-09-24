import java.util.Arrays;
import java.util.Scanner;


public class Main {
    public static void Merge(int arr[],int p,int q,int r){
        int b[] =new int[r-p+1];
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
    public static void MergeSort(int arr[],int p,int r){
        
        if (p < r) { 
            int q = (p + r) / 2; 
  
            MergeSort(arr, p, q); 
            MergeSort(arr, q + 1, r); 
  
            Merge(arr, p, q, r); 
        }
    }
    public static void main(String[] args){

        Scanner scan = new Scanner(System.in);
        int input,size;
        size = scan.nextInt();

        int [] array = new int[size];
        for (int i = 0; i < size; i++){
                input = scan.nextInt();
                array[i] = input;
        }
        
        float tinicio, tfinal, tiempo;

        tinicio = System.nanoTime();
        MergeSort(array,0,size-1);
        tfinal = System.nanoTime();
        tiempo = tfinal -tinicio;
        System.out.print(tiempo/1000000000);
    }
}
