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

arr = [1,3,6,7,3,7,8,6,4]

print(arr)
countSort(arr)
print(arr)

