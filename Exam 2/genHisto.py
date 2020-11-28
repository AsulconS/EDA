import sys
import cv2
import numpy as np
import matplotlib.pyplot as plt

def genUnique(filename, plotting):
    p = f'./{filename}'
    img = cv2.imread(p)
    if img is None:
        print('ERROR: Cannot Found or Read', p)
    else:
        dimensions = img.shape

        n, _, _ = plt.hist(x=img.ravel(), bins=256, range=[0,256], color='orange')
        file = open(f'./{filename[:-4]}', 'w')
        file.write(f'{dimensions[0] * dimensions[1]} {n.mean()}\n')
        file.write(' '.join(list(map(str, map(int, n)))))
        file.write('\n')
        file.close()

        if plotting:
            plt.style.use('ggplot')
            color = ('Blue', 'Green', 'red')
            for i, col in enumerate(color):
                plt.hist(x=img[:, :, i].ravel(), bins=256, range=[0,256], color=col, alpha=0.5)

            plt.xlabel('Intensity Value')
            plt.ylabel('Count')
            plt.legend(['Total', 'Blue Channel', 'Green Channel', 'Red Channel'])
            plt.show()

def genMultiple(datasize, plotting):
    for i in range(8):
        for j in range(datasize):
            p = f'./imgDataset/{i}/{j}.jpg'
            img = cv2.imread(p)
            if img is None:
                continue

            dimensions = img.shape

            n, _, _ = plt.hist(x=img.ravel(), bins=256, range=[0,256], color='orange')
            file = open(f'./dataset/{i}/{j}', 'w')
            file.write(f'{dimensions[0] * dimensions[1]} {n.mean()}\n')
            file.write(' '.join(list(map(str, map(int, n)))))
            file.write('\n')
            file.close()

            if plotting:
                plt.style.use('ggplot')
                color = ('Blue', 'Green', 'red')
                for i, col in enumerate(color):
                    plt.hist(x=img[:, :, i].ravel(), bins=256, range=[0,256], color=col, alpha=0.5)

                plt.xlabel('Intensity Value')
                plt.ylabel('Count')
                plt.legend(['Total', 'Blue Channel', 'Green Channel', 'Red Channel'])
                plt.show()

def main():
    if len(sys.argv) < 2:
        print('Ussage: python{3} genHisto.py [--args] [filename]')
        return

    error_raise = False

    args = []
    filename = None
    filename_raise = False
    for i in range(1, len(sys.argv)):
        if sys.argv[i][:2] == '--':
            args.append(sys.argv[i])
        elif filename is None:
            filename = sys.argv[i]
            args.append(sys.argv[i])
        else:
            filename_raise = True

    plotting = False
    if '--plot' in args:
        plotting = True

    if '--unique' in args:
        if '--multiple' in args:
            print('ERROR: --unique and --multiple are mutually exclusive')
            error_raise = True
        if filename is None:
            print('ERROR: filename not found')
            error_raise = True
        elif filename_raise:
            print('ERROR: too much filenames given')
            error_raise = True

        if not error_raise:
            genUnique(filename, plotting)
    elif '--multiple' in args:
        if '--unique' in args:
            print('ERROR: --unique and --multiple are mutually exclusive')
            if filename is None:
                print('ERROR: filename not found')
            elif filename_raise:
                print('ERROR: too much filenames given')
            error_raise = True
        if args.index('--multiple') < len(args) - 1:
            datasize = args[args.index('--multiple') + 1]
            if not datasize.isdigit():
                print('ERROR: --multiple must be followed by a number')
                error_raise = True
        else:
            print('ERROR: --multiple must be followed by a number')
            error_raise = True

        if not error_raise:
            genMultiple(int(datasize), plotting)


if __name__ == '__main__':
    main()
