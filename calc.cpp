#include"point.h"
string cascadeName = "haarcascade_frontalface_alt.xml";
ofstream out_txt("result.txt");
void detect_face(string fin_name_txt)
{
	Mat frame, frameCopy, image;
	bool tryflip = false;
	CascadeClassifier cascade;
	double scale = 1;
	cascade.load( cascadeName );
	int k = 1;
	
		//提取图片的路径名字
		vector<string> img_name_1;//这是预留参数
		vector<string> *imName1=get_csv(fin_name_txt,img_name_1);
		for(unsigned int i_name = 0;i_name < imName1->size();\
			i_name++)
		{
			string dir = imName1->at(i_name);
			//getline(in_txt,inputName);//读取图片路径
			//dir=inputName;
			//dir+=".jpg";
			cout<<dir<<endl;
			image = imread(dir,CV_LOAD_IMAGE_COLOR);
			if(image.empty())
			{
				cout<<"此处图片读取错误"<<endl;
				system("pause");
			}
			if( !image.empty() )
			{
				int scoreBuffer[500];
				vector<Rect> faces=detectAndDraw( image, cascade,scale,scoreBuffer);
				out_txt<<dir<<endl;
				out_txt<<faces.size()<<endl;
				//out_txt.close();
				if(faces.size()==0)
				{
					cout<<"未检测到人脸"<<endl;
				}
				for(int i=0;i<faces.size();i++)
				{
					out_txt<<faces[i].x<<" "<<faces[i].y\
						<<" "<<faces[i].width<<" "<<faces[i].\
						height<<" "<<scoreBuffer[i]<<endl;
				}
				faces.clear();
			}
			k++;
	}
	out_txt.close();
	
}

vector<Rect> detectAndDraw( Mat& img, CascadeClassifier& cascade,
	double scale,int * scoreBuffer)
{
	vector<Rect> faces, faces2;
	Mat gray, smallImg( cvRound (img.rows/scale), cvRound(img.cols/scale), CV_8UC1 );

	cvtColor( img, gray, CV_BGR2GRAY );
	resize( gray, smallImg, smallImg.size(), 0, 0, INTER_LINEAR );
	equalizeHist( smallImg, smallImg );
	//检测出人脸位置
	
	cascade.detectMultiScale( smallImg, faces,1.05,0, 0|CV_HAAR_SCALE_IMAGE,Size(40, 40));
	cout<<faces.size()<<"he"<<faces2.size()<<endl;
	//至少有三次重叠检测才认为人脸确实存在
	cascade.detectMultiScale( smallImg, faces2,1.05,3, 0|CV_HAAR_SCALE_IMAGE,Size(40, 40));
	// 1.05  2 是最小检测窗口和最大检测窗口
	int i=0;
	if(faces2.size() > 500 || faces.size() > 500)
	{
		cout<<"分数数组越界，请扩大分数的数组空间"<<endl;
		/*exit(0);*/
		//system("pause");
		faces.clear();
		faces2.clear();
		
	}
	for( vector<Rect>::const_iterator r = faces2.begin(); r != faces2.end(); r++,i++)
	{
		 //计算每张脸的准确率分值，
		 int score=0;
		 for( vector<Rect>::const_iterator s = faces.begin(); s != faces.end(); s++)
		 {
			 if(isOverlap(*r,*s))//如果重复就说明这个子矩形框是正确的，可以加分
			 {
				score++;
				//rectangle(img,*s,Scalar(255,0,0));
			 }
		 }
		 //rectangle(img,*r,Scalar(0,0,255));
		 cout<<"分数"<<score<<endl;
		 scoreBuffer[i]=score;
		 //cout<<score<<endl;
	}
	//imshow("ceshiss",img);
	return faces2;
}
bool isOverlap(Rect r1,Rect r2)//判断矩形是否重叠
{

	int x0=r1.x>r2.x?r1.x:r2.x;
	int y0=r1.y>r2.y?r1.y:r2.y;
	int x1=r1.x+r1.width;
	int y1=r1.y+r1.height;
	int x2=r2.x+r2.width;
	int y2=r2.y+r2.height;
	int x3=x1<x2?x1:x2;
	int y3=y1<y2?y1:y2;
	if(x3<x0||y3<y0)
	{
		return false;
	}
	else
	{
		return true;
	}
}


double setUnion(IplImage* face1,IplImage* face2 )
{
	int nNZ = 0;
	//这里的循环结束条件与Mat是不一样的
	uchar *data = (uchar *)face1->imageData;
	uchar *data1 = (uchar *)face2->imageData;
	for(int i = 0;i < face1->height;i++)
	{
		for(int j = 0;j < face1->width;j++)
		{
			uchar a_p=data[i*(face1->widthStep/sizeof(uchar)) + j];
			uchar b_p=data1[i*(face2->widthStep/sizeof(uchar)) + j];
			if( a_p == 0 || b_p==0)
			{
				nNZ +=1;	
			}
		}
	}
	double areaDbl = (double)nNZ;
	if(areaDbl == 0)
	{
		return 1;
	}
	cout<<"并集"<<areaDbl<<endl;
	return areaDbl;
}

double setIntersect(IplImage* face1,IplImage* face2 )
{
	int nNZ = 0;
	//这里的循环结束条件与Mat是不一样的
	uchar *data = (uchar *)face1->imageData;
	uchar *data1 = (uchar *)face2->imageData;
	for(int i = 0;i < face1->height;i++)
	{
		for(int j = 0;j < face1->width;j++)
		{
			uchar a_p=data[i*(face1->widthStep/sizeof(uchar)) + j];
			uchar b_p=data1[i*(face2->widthStep/sizeof(uchar)) + j];
			if(a_p == b_p && a_p == 0 && b_p==0)
			{
				nNZ +=1;	
			}
		}
	}
	double areaDbl = (double)nNZ;
	if(areaDbl == 0)
	{
		return 1;
	}
	cout<<"交集"<<areaDbl<<endl;
	return areaDbl;
}

double computeScore(IplImage* face1,IplImage* face2)
{
	double score = setIntersect(face1,face2)\
		/(setUnion(face1,face2));
	return score;
}

vector<string> *get_csv(string file_csv_name,vector<string> img_name)
{
	vector<string> *imNames = new vector<string>;
	//输入文件流的头指针
	ifstream fin(file_csv_name);
	string line1,line;
	getline(fin,line1);
	//cout<<"csv文件头"<<line1<<endl;
	while(getline(fin,line))
	{
		//从第二行开始保存读入的数据
		istringstream sin(line);
		vector<string> fileds;
		string filed;
		while(getline(sin,filed,','))
		{
			//每个字符添加到向量中
			fileds.push_back(filed);
		}
		string name = fileds[0];
		//指针的vector放入使用->
		imNames->push_back(name);

	}
	fin.close();
	return imNames;
}