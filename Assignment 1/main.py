
import os

def MakeCommand(language,algorithm,input):
    if language == "C++":
        return "g++ "+algorithm+"/"+algorithm+".cpp && ./a.out < "+input+" && rm a.out"
    if language == "Python":
        return "python "+algorithm+"/"+algorithm+".py < "+input
    if language == "Java":
        return "java "+algorithm+"/"+algorithm+".java < "+input


Languages = ["C++","Python","Java"]

Algorithms = ["MergeSort","QuickSort","InsertSort","BubbleSort","SelectionSort","CountingSort","HeapSort"]

Entradas = ["input.txt"]

for i in Languages:
    for j in Algorithms:
        print(i," ",j)
        for k in Entradas:
            command = MakeCommand(i,j,k)
            os.system(command)

