import java.util.Arrays;

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
        int[] arr = {49, 27, 40, 59, 13, 55, 38, 2, 62, 48, 37, 4, 44, 22, 3, 51};
        quickSort(arr, 16);
        System.out.println(Arrays.toString(arr));
    }
}
