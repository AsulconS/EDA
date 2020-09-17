import random
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
archivo = open("input.txt").readlines()
print(archivo)
n = int(archivo[0])
datos = map(int,archivo[1].split())
arr = list(datos)

#medir tiempos
start = time()
SelectionSort(arr)
finish = time()

#output en un archivo
with open('output.txt', 'w') as f:
    sys.stdout = f # Change the standard output to the file we created.
    print(n)
    print(finish-start)
