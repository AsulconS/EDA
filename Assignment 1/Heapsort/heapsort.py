def heapify(array):
    for i in range(1, len(array)):
        j = i
        while j > 0 and array[j] > array[(j - 1) // 2]:
            array[j], array[(j - 1) // 2] = array[(j - 1) // 2], array[j]
            j = (j - 1) // 2


def heapsort(array):
    heapify(array)

    for k in range(len(array) - 1, 0, -1):
        array[0], array[k] = array[k], array[0]

        j = 0
        while True:
            largest = j
            left = 2 * j + 1
            right = 2 * j + 2

            if left < k and array[left] > array[largest]:
                largest = left
            if right < k and array[right] > array[largest]:
                largest = right
            if largest == j:
                break

            array[j], array[largest] = array[largest], array[j]
            j = largest


if __name__ == '__main__':
    arr = [49, 27, 40, 59, 13, 55, 38, 2, 62, 48, 37, 4, 44, 22, 3, 51]
    heapsort(arr)
    print(arr)
