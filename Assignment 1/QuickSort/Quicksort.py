def partition(array, p, r):
    pivot = array[r]
    i = p - 1
    for j in range(p, r):
        if array[j] <= pivot:
            i = i + 1
            array[i], array[j] = array[j], array[i]
    array[i + 1], array[r] = array[r], array[i + 1]
    return i + 1


def quicksort_r(array, p, r):
    if p < r:
        q = partition(array, p, r)
        quicksort_r(array, p, q - 1)
        quicksort_r(array, q + 1, r)


def quicksort(array):
    quicksort_r(array, 0, len(array) - 1)

arr = [49, 27, 40, 59, 13, 55, 38, 2, 62, 48, 37, 4, 44, 22, 3, 51]
quicksort(arr)
print(arr)
