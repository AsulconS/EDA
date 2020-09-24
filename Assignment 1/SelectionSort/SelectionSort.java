import java.util.Arrays;
import java.util.Scanner;

class SelectionSort 
{ 
	public static void sort(int arr[]) 
	{ 
		int size = arr.length; 
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

 
	public static void main(String args[]) 
	{ 

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
        sort(array); 
        tfinal = System.nanoTime();
        tiempo = tfinal -tinicio;
        System.out.print(tiempo/1000000000);

	} 
} 

