#!/usr/bin/python
# -*- coding: utf-8 -*-
import os
# import json
import numpy as np
# import pandas as pd
# import cv2
import sys
# import shutil
# print "hello"
# import argparse
# import csv
import pylab as pl
def plot_detect(data_cal):
    file = open(data_cal)
    lines = file.readlines()
    list_cla = []
    list_cal_1 = []
    for line in lines:

        line_split = line.split(',')
        line_1 = float(line_split[0])
        line_2 = float(line_split[1])
        line_3 = int(line_split[2])
        # print(line_3)
        if line_3 < 100:
            print(line_3)
            list_cal_1.append(line_3)
            list_cla.append(line_1)

#     绘图
    x = list_cal_1
    y = list_cla
    pl.plot(x,y)
    pl.grid()
    pl.grid(color ='r',linewidth = '0.05',linestyle = '--')
    pl.show()



if __name__ == '__main__':
    # file_1 = './face_detect/out_test.csv'
    file_1 = 'know_1.csv'

    plot_detect(file_1)