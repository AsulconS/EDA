import java.util.Arrays;
import java.util.Scanner;

public class Counting {

      public static int max(int arr[]){
            int maximo = arr[0];

            for(int i = 1; i < arr.length; ++i)
                  if(maximo < arr[i])
                        maximo = arr[i];

            return maximo;
      }

      public static void sort(int arr[]) {
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
