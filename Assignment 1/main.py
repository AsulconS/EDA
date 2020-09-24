
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

#"C++","Java","Python"

Algorithms = ["MergeSort","QuickSort","CountingSort","HeapSort"]

#"SelectionSort","MergeSort","QuickSort","CountingSort","HeapSort","BubbleSort","InsertSort"


#arreglo para los tamaños de las pruebas (hasta 1 millon max input.txt)

Tamanios = []
for i in range (10000,50000,5000):
    Tamanios.append(i)

# numero de repeticiones de la misma prueba

n_repeat = 3

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




