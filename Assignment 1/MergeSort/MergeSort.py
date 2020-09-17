import random
import sys
from time import time


def Merge(arr,p,q,r):
    x = p
    y = r
    arr2 = arr.copy()
    for i in range(r-q):
        arr2[r-i]=arr[q+i+1]
    for i in range(r-p):
        if(arr2[x] > arr2[y]):
            arr[p+i]=arr2[x]
            x=x+1
        else:
            arr[p+i]=arr2[y]
            y=y-1
    arr[r]=arr2[x]

def MergeSort(arr,p,r):
    if(p<r):
        q = (r+p)//2
        MergeSort(arr,p,q)
        MergeSort(arr,q+1,r)
        Merge(arr,p,q,r)

#input de datos
archivo = open("input.txt").readlines()
print(archivo)
n = int(archivo[0])
datos = map(int,archivo[1].split())
arr = list(datos)

#medir tiempos
start = time()
MergeSort(arr, 0, len(arr)-1)
finish = time()

#output en un archivo
with open('output.txt', 'w') as f:
    sys.stdout = f # Change the standard output to the file we created.
    print(n)
    print(finish-start)