import sys
import cv2
import numpy as np
import matplotlib.pyplot as plt

def main():
    if len(sys.argv) < 3:
        return

    p = f'./{sys.argv[2]}'
    img = cv2.imread(p)
    if img is None:
        print('Cannot Found or Read', p)
    else:
        dimensions = img.shape

        n, _, _ = plt.hist(x=img.ravel(), bins=256, range=[0,256], color='orange')
        file = open(f'./{sys.argv[2][:-4]}', 'w')
        file.write(f'{dimensions[0] * dimensions[1]} {n.mean()}\n')
        file.write(' '.join(list(map(str, map(int, n)))))
        file.write('\n')
        file.close()

    for i in range(8):
        for j in range(int(sys.argv[1]) + 1):
            p = f'./imgDataset/{i}/{j}.jpg'
            img = cv2.imread(p)
            if img is None:
                print('Cannot Found or Read', p)
                continue

            dimensions = img.shape

            n, _, _ = plt.hist(x=img.ravel(), bins=256, range=[0,256], color='orange')
            file = open(f'./dataset/{i}/{j}', 'w')
            file.write(f'{dimensions[0] * dimensions[1]} {n.mean()}\n')
            file.write(' '.join(list(map(str, map(int, n)))))
            file.write('\n')
            file.close()

    return # remove this for plotting

    plt.style.use('ggplot')
    color = ('Blue', 'Green', 'red')
    for i, col in enumerate(color):
        plt.hist(x=img[:, :, i].ravel(), bins=256, range=[0,256], color=col, alpha=0.5)

    plt.xlabel('Intensity Value')
    plt.ylabel('Count')
    plt.legend(['Total', 'Blue Channel', 'Green Channel', 'Red Channel'])
    plt.show()


if __name__ == '__main__':
    main()
