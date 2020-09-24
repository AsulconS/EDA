#include <iostream>

using namespace std;

void swap(int& a, int& b)
{
    int temp {a};
    a = b;
    b = temp;
}

void heapify(int* arr, int n)
{
    for(int i {1}; i < n; ++i)
    {
        int j {i};
        while(j > 0 && arr[j] > arr[(j - 1) / 2])
        {
            swap(arr[j], arr[(j - 1) / 2]);
            j = (j - 1) / 2;
        }
    }
}

void heapsort(int* arr, int n)
{
    heapify(arr, n);

    for(int k {n - 1}; k > 0; --k)
    {
        swap(arr[0], arr[k]);

        int largest, left, right;

        int j {0};
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

            swap(arr[j], arr[largest]);
            j = largest;
        }
    }
}

int main()
{

    int input,size;
    cin >> size;
    int array[size];
    for(int i = 0 ; i < size ; i++ )
    {
        cin >> input;
        array[i] = input;
    }
    
    unsigned t0,t1;

    t0 = clock();
    heapsort(array, size);
    t1 = clock();

    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    cout << time ;

    return 0;
}
