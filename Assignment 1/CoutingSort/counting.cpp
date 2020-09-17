#include <iostream>

int maxNum(int* data, int size)
{
    int maximo = data[0];
    for (size_t i = 1; i < size; i++)
    {
        if(data[i] > maximo)
            maximo = data[i];
    }
    return maximo;
}

void countingSort(int* data, int size)
{
    int maximo = maxNum(data,size) + 1;

    int* output = new int[size];
    int* index = new int[maximo] {0};

    for(size_t i = 0; i < size; ++i) // Counts numbers
        ++index[data[i]];
    for(size_t i = 1; i < maximo; ++i) // Sums the Indices
        index[i] += index[i - 1];
    for(int i = size - 1; i >= 0; --i) // Assign the correct ones
        output[--index[data[i]]] = data[i];

    for(size_t i = 0; i < size; ++i)
        data[i] = output[i];

    delete[] output;
    delete[] index;
}

int main()
{
    int arr[] = {1, 4, 1, 2, 7, 5, 2};
    for(size_t i = 0; i < 7; ++i)
        std::cout << arr[i] << ' ';
    std::cout << std::endl;

    countingSort(arr, 7);
    for(size_t i = 0; i < 7; ++i)
        std::cout << arr[i] << ' ';
    std::cout << std::endl;

    return 0;
}