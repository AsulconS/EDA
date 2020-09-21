import sys
from time import time


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

#input de datos
archivo = sys.stdin.readlines()
n = int(archivo[0])
datos = map(int,archivo[1].split())
arr = list(datos)

#medir tiempos
start = time()
quicksort(arr)
finish = time()

print(n,finish-start)


