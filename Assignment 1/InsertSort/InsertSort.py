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
archivo = sys.stdin.readlines()
n = int(archivo[0])
datos = map(int,archivo[1].split())
arr = list(datos)

#medir tiempos
start = time()
insert(arr, len(arr))
finish = time()

print(n,finish-start)
