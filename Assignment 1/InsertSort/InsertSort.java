import java.util.Arrays;
import java.util.Scanner;

public class insercion{

    public static void inser(int arr[], int tam){
        int aux, pos;
        for (int i=0;i<tam;i++){
            pos=i;//guarda la posicion
            aux=arr[i];//numero del arreglo
            while((pos>0)&&(arr[pos-1]>aux)){
                arr[pos]=arr[pos-1];
                pos--;//iteraciones hacia atras
            }
            arr[pos]=aux;
        }
    }

    public static void main(String args[]){

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
        inser(array, size);
        tfinal = System.nanoTime();
        tiempo = tfinal -tinicio;
        System.out.print(tiempo/1000000000);
    }
}
