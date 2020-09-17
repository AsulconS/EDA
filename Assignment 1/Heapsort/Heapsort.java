import java.util.Arrays;

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
        int[] arr = {49, 27, 40, 59, 13, 55, 38, 2, 62, 48, 37, 4, 44, 22, 3, 51};
        heapsort(arr, 16);
        System.out.println(Arrays.toString(arr));
    }
}
