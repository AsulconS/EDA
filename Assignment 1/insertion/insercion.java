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
        inser(arr, tam);
        tfinal = System.currentTimeMillis();
        /*for (int i = 0; i < tam; i++){
             System.out.println("valor " + arr[i]);
        }*/
        tiempo = tfinal -tinicio;
        System.out.println(tam + " " + tiempo);
       
    }
}