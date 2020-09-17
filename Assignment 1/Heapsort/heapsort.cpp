#include <iostream>

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
    int* arr {new int[16] {49, 27, 40, 59, 13, 55, 38, 2, 62, 48, 37, 4, 44, 22, 3, 51}};
    heapsort(arr, 16);

    std::cout << '[';
    for(int i {0}; i < 15; ++i)
    {
        std::cout << arr[i] << ", ";
    }
    std::cout << arr[15] << ']' << std::endl;

    delete[] arr;
    return 0;
}
