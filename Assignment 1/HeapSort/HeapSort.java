import java.util.Arrays;
import java.util.Scanner;

public class Heapsort
{
    private static void heapify(int[] arr, int n)
    {
        for(int i = 1; i < n; ++i)
        {
            int j = i;
            while(j > 0 && arr[j] > arr[(j - 1) / 2])
            {
                int temp = arr[j];
                arr[j] = arr[(j - 1) / 2];
                arr[(j - 1) / 2] = temp;
                j = (j - 1) / 2;
            }
        }
    }

    private static void heapsort(int[] arr, int n)
    {
        heapify(arr, n);

        for(int k = n - 1; k > 0; --k)
        {
            int temp = arr[0];
            arr[0] = arr[k];
            arr[k] = temp;

            int largest, left, right;

            int j = 0;
            while(true)
            {
                largest = j;
                left  = 2 * j + 1;
                right = 2 * j + 2;

                if(left < k && arr[left] > arr[largest])
                {
                    largest = left;
                }
                if(right < k && arr[right] > arr[largest])
                {
                    largest = right;
                }
                if(largest == j)
                {
                    break;
                }

                temp = arr[j];
                arr[j] = arr[largest];
                arr[largest] = temp;
                j = largest;
            }
        }
    }

    public static void main(String[] args)
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
        heapsort(array, size);
        tfinal = System.nanoTime();
        tiempo = tfinal -tinicio;
        System.out.print(tiempo/1000000000);
    }
}
