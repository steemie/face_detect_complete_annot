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

//�����������εĽ������
double setIntersect(IplImage* face1,IplImage* face2 );
//�����������β���
double setUnion(IplImage* face1,IplImage* face2 );
//�������
double computeScore(IplImage* face1,IplImage* face2);
//������������ɼ�����txt�ļ�
void detect_face(string fin_name_txt);

bool isOverlap(Rect r1,Rect r2);
//ʵ��ʶ�𲢻��Ƴ��沿���ο򣬲���������ͼƬ�����������������������С�ȣ���������׼ȷ��ֵ��
//���ؼ�������������
vector<Rect> detectAndDraw( Mat& img, CascadeClassifier& cascade,double scale,int * score);
//����ģ���ļ���Ϊxml�ļ��ṹ��¼��һ����׼������ģ������;
//����csv�ļ�����
vector<string> *get_csv(string file_csv_name,vector<string> img_name);
#endif