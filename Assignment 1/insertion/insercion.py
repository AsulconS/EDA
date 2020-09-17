import random
import sys
from time import time

def insert(arr, tam):
   
    for i in range (tam):
        pos = i
        aux = arr[i]
        while(pos> 0) and (arr[pos-1] > aux):
            arr[pos] = arr[pos-1]
            pos = pos -1
        arr[pos] = aux

#input de datos
archivo = open("input.txt").readlines()
print(archivo)
n = int(archivo[0])
datos = map(int,archivo[1].split())
arr = list(datos)

#medir tiempos
start = time()
insert(arr, len(arr))
finish = time()

#output en un archivo
with open('output.txt', 'w') as f:
    sys.stdout = f # Change the standard output to the file we created.
    print(n)
    print(finish-start)
