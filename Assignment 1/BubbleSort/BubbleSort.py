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
archivo = sys.stdin.readlines()
n = int(archivo[0])
arr = []
for dato in archivo[1].split():
    arr.append(int(dato))
 


#medir tiempos
start = time()
bur(arr, len(arr))
finish = time()

print(n,finish-start)





