import matplotlib.patches as mpatches
import matplotlib.pyplot as plt

def main():
    x = []
    y = []
    z = []
    c = []

    inputFile = open('./plot/data.pt', 'r')
    for line in inputFile:
        point = list(map(float, line.split()[:-1]))
        x.append(point[0])
        y.append(point[1])
        z.append(point[2])
        c.append(int(line[-2:-1]))

    colors = ['black', 'red', 'orange', 'yellow', 'green', 'cyan', 'blue', 'orchid']
    c = [colors[i] for i in c]

    plt.style.use('ggplot')

    fig = plt.figure()
    ax = fig.add_subplot(111)

    ax.scatter(x, y, c=c)
    ax.set_xlabel('Image Balance (Curtosis)')
    ax.set_ylabel('Image Intensity Centering')

    plt.show()

if __name__ == '__main__':
    main()
