#include <iostream>

template <typename T>
void swap(T& v1, T& v2)
{
    T t = v1;
    v1 = v2;
    v2 = t;
}

template <typename T>
int partition(T* data, int low, int high)
{
    T pivot = data[high];
    int i = low - 1;
    for(size_t j = low; j < high; ++j)
    {
        if(data[j] < pivot)
            swap<T>(data[j], data[++i]);
    }
    swap<T>(data[high], data[i + 1]);
    return i + 1;
}

template <typename T>
void quick(T* data, int low, int high)
{
    if(low >= high)
        return;
    int partI = partition<T>(data, low, high);
    quick<T>(data, low, partI - 1);
    quick<T>(data, partI + 1, high);
}

template <typename T>
void quickSort(T* data, int size)
{
    quick<T>(data, 0, size - 1);
}

int main()
{
    int arr[] = {10, 80, 30, 90, 40, 50, 70};
    for(size_t i = 0; i < 7; ++i)
        std::cout << arr[i] << ' ';
    std::cout << std::endl;

    quickSort<int>(arr, 7);
    for(size_t i = 0; i < 7; ++i)
        std::cout << arr[i] << ' ';
    std::cout << std::endl;

    return 0;
}
