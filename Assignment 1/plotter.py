import re as re
import numpy as np
import matplotlib.patches as mpatches
import matplotlib.pyplot as plt


def main():
    lang_raw_lst = ['C++', 'Java', 'Python']
    algo_raw_lst = ['MergeSort', 'QuickSort', 'CountingSort', 'HeapSort']
    clrs_raw_lst = ['blue', 'red', 'cyan', 'green', 'pink', 'olive', 'brown']

    measurements = {}

    key = None
    f = open('output.txt', 'r')
    for line in f:
        ls = line.split()
        if ls[0] in lang_raw_lst:
            key = ls[0] + ls[1]
            measurements[key] = [[], []]
        else:
            measurements[key][0].append(ls[0])
            measurements[key][1].append(sum(map(float, ls[1:])) / (len(ls) - 1))

    for key, value in measurements.items():
        print(f'{key} -> {value}')

    # 1
    for algo in algo_raw_lst:
        x_ticks_lbl = [str(int(x) // 1000) + 'k' for x in measurements[lang_raw_lst[0] + algo][0]]
        x_ticks = np.arange(len(x_ticks_lbl))
        plt.xticks(x_ticks, x_ticks_lbl, rotation='vertical')

        keys = []
        patches = []
        color_index = 0
        for lang in lang_raw_lst:
            keys.append(lang + algo)
            patches.append(mpatches.Patch(color=clrs_raw_lst[color_index], label=(lang + ' ' + algo)))
            color_index = color_index + 1

        plt.legend(handles=patches)
        plt.xlabel('n')
        plt.ylabel('time (s)')

        plt.suptitle(algo)

        color_index = 0
        for key in keys:
            y_axis = list(map(float, measurements[key][1]))
            plt.plot(x_ticks, y_axis, 'tab:' + clrs_raw_lst[color_index])
            color_index = color_index + 1

        y_max_temp = 4.5
        plt.ylim([0, y_max_temp])

        y_ticks_lbl = list(map(str, [round(x, 1) for x in np.arange(0, y_max_temp + 0.5, 0.5)]))
        y_ticks = list(map(float, y_ticks_lbl))

        plt.yticks(y_ticks, y_ticks_lbl)
        plt.grid(linestyle='dotted')
        plt.show()

    # 2
    for lang in lang_raw_lst:
        x_ticks_lbl = [str(int(x) // 1000) + 'k' for x in measurements[lang + algo_raw_lst[0]][0]]
        x_ticks = np.arange(len(x_ticks_lbl))
        plt.xticks(x_ticks, x_ticks_lbl, rotation='vertical')

        keys = []
        patches = []
        color_index = 0
        for algo in algo_raw_lst:
            keys.append(lang + algo)
            patches.append(mpatches.Patch(color=clrs_raw_lst[color_index], label=(lang + ' ' + algo)))
            color_index = color_index + 1

        plt.legend(handles=patches)
        plt.xlabel('n')
        plt.ylabel('time (s)')

        plt.suptitle(lang)

        color_index = 0
        for key in keys:
            y_axis = list(map(float, measurements[key][1]))
            plt.plot(x_ticks, y_axis, 'tab:' + clrs_raw_lst[color_index])
            color_index = color_index + 1

        y_max_temp = 4.5
        plt.ylim([0, y_max_temp])

        y_ticks_lbl = list(map(str, [round(x, 1) for x in np.arange(0, y_max_temp + 0.5, 0.5)]))
        y_ticks = list(map(float, y_ticks_lbl))

        plt.yticks(y_ticks, y_ticks_lbl)
        plt.grid(linestyle='dotted')
        plt.show()


if __name__ == '__main__':
    main()
