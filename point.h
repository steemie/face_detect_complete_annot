#ifndef POINT
#define POINT
#include<iostream>
#include<highgui.h>
#include<opencv.hpp>

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <cctype>
#include<fstream>
#include <iterator>
#include <stdio.h>

#include<sstream>
#include<string>
#include<vector>

using namespace std;
using namespace cv;

//计算两个矩形的交集面积
double setIntersect(IplImage* face1,IplImage* face2 );
//计算两个矩形并集
double setUnion(IplImage* face1,IplImage* face2 );
//计算分数
double computeScore(IplImage* face1,IplImage* face2);
//检测人脸，生成检测出的txt文件
void detect_face(string fin_name_txt);

bool isOverlap(Rect r1,Rect r2);
//实现识别并绘制出面部矩形框，参数依次是图片，人脸检测分类器，允许的缩小比，检测出人脸准确分值，
//返回检测出的人脸矩形
vector<Rect> detectAndDraw( Mat& img, CascadeClassifier& cascade,double scale,int * score);
//人脸模型文件，为xml文件结构记录了一个标准的人脸模特数据;
//处理csv文件数据
vector<string> *get_csv(string file_csv_name,vector<string> img_name);
#endif