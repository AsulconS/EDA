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
        Scanner in = new Scanner(System.in);
        int tam;
        tam = in.nextInt();

        int [] arr = new int[tam];
        for (int i = 0; i < tam; i++){
            int aleatorio = (int) (Math.random()*tam)+1;
            arr[i] = aleatorio;
        }
        
        long tinicio, tfinal, tiempo;

        tinicio = System.currentTimeMillis();
        bur(arr, tam);
        tfinal = System.currentTimeMillis();
        tiempo = tfinal -tinicio;
        System.out.println(tam + " " + tiempo);
    }
}


