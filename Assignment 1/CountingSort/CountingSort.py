import sys
from time import time

def countSort(arr): 

	maximo = max(arr) + 1
	output = [0 for i in range(len(arr))] 
	count = [0 for i in range(maximo)] 


	for i in arr: 
		count[i] += 1

	for i in range(1,maximo): 
		count[i] += count[i-1] 

	for i in range(len(arr)-1, -1, -1): 
		output[count[arr[i]]-1] = arr[i] 
		count[arr[i]] -= 1

	for i in range(len(arr)): 
		arr[i] = output[i] 
	return arr 

#input de datos
archivo = sys.stdin.readlines()
n = int(archivo[0])
arr = []

dato = archivo[1].split()
for i in range (n):
    arr.append(int(dato[i]))

#medir tiempos
start = time()
countSort(arr)
finish = time()

print(finish-start,end = '')



