import os


def setTam(size):
    f = open("inputs/input.txt", "r")
    lines = f.readlines()
    lines[0] = str(size) + '\n'
    f.close()
    g = open("inputs/input.txt", "w")
    for line in lines:
        g.write(line)
    g.close()


def MakeCommand(language,algorithm,input):
    if language == "C++":
        return "g++ "+algorithm+"/"+algorithm+".cpp && ./a.out < inputs/input.txt"+" && rm a.out"
    if language == "Python":
        return "python "+algorithm+"/"+algorithm+".py < inputs/input.txt"
    if language == "Java":
        return "java "+algorithm+"/"+algorithm+".java < inputs/input.txt"


Languages = ["C++","Java","Python"]

Algorithms = ["SelectionSort","MergeSort","QuickSort","CountingSort","HeapSort","BubbleSort","InsertSort"]

Tamanios = [10000]

n_repeat = 1


for i in Languages:
    for j in Algorithms:
        name_command = "echo "+ i + " " + j
        os.system(name_command)
        for k in Tamanios:
            tam = "echo -n '"+ str(k) + " '"
            os.system(tam)
            for l in range(n_repeat):
                setTam(k)
                command = MakeCommand(i,j,k)
                os.system(command)
                os.system("echo -n ' '")
            os.system("echo ' '")
