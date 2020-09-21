import java.util.Arrays;
import java.util.Scanner;

public class Quicksort
{
    private static int partition(int[] arr, int p, int r)
    {
        int pivot = arr[r];
        int i = p - 1;
        for(int j = p; j < r; ++j)
        {
            if(arr[j] <= pivot)
            {
                ++i;
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        int temp = arr[i + 1];
        arr[i + 1] = arr[r];
        arr[r] = temp;
        return i + 1;
    }

    private static void quickSortR(int[] arr, int p, int r)
    {
        if(p < r)
        {
            int q = partition(arr, p, r);
            quickSortR(arr, p, q - 1);
            quickSortR(arr, q + 1, r);
        }
    }

    private static void quickSort(int[] arr, int n)
    {
        quickSortR(arr, 0, n - 1);
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
        quickSort(array, size);
        tfinal = System.nanoTime();
        tiempo = tfinal -tinicio;
        System.out.println(size+" "+tiempo/1000000000);

    }
}
