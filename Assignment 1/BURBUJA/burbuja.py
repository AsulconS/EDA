import random
import sys
from time import time

def bur(arr, tam):
    for i in range (tam):
       for j in range (tam-1):
           if(arr[j] < arr [j+1]):
               tem = arr[j]
               arr[j] = arr[j+1]
               arr[j+1] = tem

#input de datos
archivo = open("input.txt").readlines()
print(archivo)
n = int(archivo[0])
datos = map(int,archivo[1].split())
arr = list(datos)

#medir tiempos
start = time()
bur(arr, len(arr))
finish = time()

#output en un archivo
with open('output.txt', 'w') as f:
    sys.stdout = f # Change the standard output to the file we created.
    print(n)
    print(finish-start)
