import sys
from time import time


def SelectionSort(arr):
    temp = 0
    arr2 = arr.copy()
    for i in range(len(arr2)):
        minimo = i
        for j in range(i+1,len(arr2)):
            if arr2[minimo] > arr2[j]:
                minimo = j
        temp = arr2[i]
        arr2[i] = arr2[minimo]
        arr2[minimo] = temp

#input de datos
archivo = sys.stdin.readlines()
n = int(archivo[0])
datos = map(int,archivo[1].split())
arr = list(datos)

#medir tiempos
start = time()
SelectionSort(arr)
finish = time()

print(n,finish-start)


