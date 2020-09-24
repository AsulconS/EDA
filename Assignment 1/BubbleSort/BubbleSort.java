import java.util.Scanner;

public class Burbuja{
    public static void bur(int arr[], int tam){
        int tem;
        for(int i =0; i < tam; i++){
            for(int j = 0; j < tam-1; j++){
                if(arr[j] < arr[j+1]){
                    tem = arr[j];
                    arr[j] = arr[j+1];
                    arr[j+1] = tem;
                }
            }
        }
    }

    public static void main(String arg[]){
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
        bur(array, size);
        tfinal = System.nanoTime();
        tiempo = tfinal -tinicio;
        System.out.print(tiempo/1000000000);
    }
}


