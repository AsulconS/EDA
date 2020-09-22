
import os

def MakeCommand(language,algorithm,input):
    if language == "C++":
        return "g++ "+algorithm+"/"+algorithm+".cpp && ./a.out < inputs/"+input+" && rm a.out"
    if language == "Python":
        return "python "+algorithm+"/"+algorithm+".py < inputs/"+input
    if language == "Java":
        return "java "+algorithm+"/"+algorithm+".java < inputs/"+input


Languages = ["C++","Java","Python"]
#

Algorithms = ["MergeSort","QuickSort","CountingSort","HeapSort","BubbleSort","InsertSort","SelectionSort"]

#

Entradas = ["input1.txt","input2.txt","input3.txt","input4.txt","input5.txt","input6.txt","input7.txt","input8.txt","input9.txt","input10.txt"]


for i in Languages:
    for j in Algorithms:
        name_command = "echo "+ i + " " + j
        os.system(name_command)
        for k in Entradas:
            command = MakeCommand(i,j,k)
            os.system(command)

