
class SelectionSort 
{ 
	void sort(int arr[]) 
	{ 
		int size = arr.length; 
		int temp;
        for(int i = 0 ; i < size - 1 ;  i++ )
        {
            int minimo = i;
            for ( int j = i+1 ; j < size  ;  j++ )
            {
                if( arr[minimo] > arr[j] )
                    minimo = j ;
            }

            temp = arr[i];
            arr[i] = arr[minimo];
            arr[minimo] = temp;
            
        }
	} 

 
	public static void main(String args[]) 
	{ 
		SelectionSort ob = new SelectionSort(); 
		int arr[] = { 10 , 9, 8, 7, 6, 5, 4 ,3 , 2 , 1 } ;
		ob.sort(arr); 
	} 
} 

