import sys
import cv2
import numpy as np
import matplotlib.pyplot as plt

def main():
    if len(sys.argv) < 2:
        return

    plt.style.use('ggplot')

    img = cv2.imread(sys.argv[1])
    if img is None:
        print('Cannot Found or Read', sys.argv[1])
        return

    color = ('Blue', 'Green', 'red')
    n, _, _ = plt.hist(x=img.ravel(), bins=256, range=[0,256], color='orange')
    print(list(map(int, n)))
    for i, col in enumerate(color):
        plt.hist(x=img[:, :, i].ravel(), bins=256, range=[0,256], color=col, alpha=0.5)

    plt.xlabel('Intensity Value')
    plt.ylabel('Count')
    plt.legend(['Total', 'Blue Channel', 'Green Channel', 'Red Channel'])
    plt.show()


if __name__ == '__main__':
    main()
