#!/usr/bin/python
# -*- coding: utf-8 -*-
import os
import json
import numpy as np
# import pandas as pd
import cv2
import sys
import shutil
# print "hello"
import argparse
import csv



def  test_cut(path_1,path_2,path_3,path_4):
    input = open(path_1,'r')
    out = open(path_3,'w')
    csv_writer = csv.writer(out)
    # csv_writer_1 = csv.writer()
    lines = input.readlines()
    for line in lines:
        out.write(line)
    fid_1 = open(path_2)
    lines1 = fid_1.readlines()
    list_2 = []
    for line_1 in lines1:
        line_hh = line_1
        str1 = str(line_1)
        out.write(str1)
    # for i in range(len(list_2)):
    #     csv_writer.writerow(list_2[i])

    input.close()
    out.close()

    # out1 = open(path_3,'r')
    # h12 = out1.readlines()
    # out3 = open(path_4,'w')
    # for h13 in h12:
    #     h14 = h13
    #     h14.replace('"','')
    #     out3.write(h14)


    # out1.close()
    # out3.close()
if __name__=='__main__':
    path_1 = 'F:\\work\\VS1\\FDDB\\calc_score_face_2\\calc_score.cpp\\calc_score.cpp\\test2.csv'
    path_2 = 'F:\\work\\VS1\\FDDB\\calc_score_face_2\\calc_score.cpp\\calc_score.cpp\\neg1.txt'
    path_3 = 'F:\\work\\VS1\\FDDB\\calc_score_face_2\\calc_score.cpp\\calc_score.cpp\\out.csv'
    path_4 = 'F:\\work\\VS1\\FDDB\\calc_score_face_2\\calc_score.cpp\\calc_score.cpp\\out3.csv'
    test_cut(path_1,path_2,path_3,path_4
             )

