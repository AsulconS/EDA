public class Counting {

      int max(int arr[]){
            int maximo = arr[0];

            for(int i = 1; i < arr.length; ++i)
                  if(maximo < arr[i])
                        maximo = arr[i];

            return maximo;
      }

      void sort(int arr[]) {
            int n = arr.length;
            int maximo = max(arr) + 1;

            int output[] = new int[n];

            int count[] = new int[maximo];

            for (int i = 0; i < maximo; ++i)
                  count[i] = 0;

            for (int i = 0; i < n; ++i)
                  ++count[arr[i]];

            for (int i = 1; i < maximo; ++i)
                  count[i] += count[i - 1];

            for (int i = n - 1; i >= 0; i--) {
                  output[count[arr[i]] - 1] = arr[i];
                  --count[arr[i]];
            }

            for (int i = 0; i < n; ++i)
                  arr[i] = output[i];
      }

      public static void main(String args[]) {
            Counting countingSort = new Counting();
            int arr[] = { 2, 2, 1, 0, 5, 6, 2, 4, 6, 7, 5, 3, 3 };

            countingSort.sort(arr);

            for (int i = 0; i < arr.length; ++i)
                  System.out.print(arr[i] + " ");
      }
}