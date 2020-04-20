#include"point.h"
//#include"Python.h"
int main()
{
	//输入检测文件的图片位置文件
	string fin_name_txt = "test_pos1_test_neg1.txt";
	detect_face(fin_name_txt);
	//比对必须先执行完检测
	string out_csv = "know_1.csv";
	string detFile = "result.txt";
	string annotFile = "test_pos1_test_neg1.txt";
	vector<string> temp_annot;
	vector<string> *imNames = get_csv(annotFile,temp_annot);
	if(imNames == NULL)
	{
		cerr<<"No images found in the list"<<annotFile<<endl;
		//system("pause");
		return -1;
	}
	ifstream fAnnot(annotFile.c_str());
	if(!fAnnot.is_open())
	{
		cerr<<"Can not open annotations from "<<annotFile<<endl;
	}
	ifstream fDet(detFile.c_str());
	if(!fDet.is_open())
	{
		cerr<<"Can not open annotations from "<<annotFile<<endl;
	}
	string imS1;
	getline(fAnnot,imS1);
	vector<Point2d> score_cal;
	vector<Point2d> neg_true;
	vector<Point2d> neg_neg;
	for(unsigned int i_1 = 0;i_1 < imNames->size();i_1++)
	{
		if((i_1 % 1) == 0)
		{
			cout<<i_1<<"image done"<<endl;
		}
		//at操作为取出指定位置的图像名字
		string im_name = imNames->at(i_1);
		string imS2;
		//分别处理txt和csv文件
		getline(fDet,imS2);
		string name_det = imS2;
		string number_face_det;
		getline(fDet,number_face_det);
		stringstream number_face(number_face_det);
		int number;
		//cout<<"hahah"<<endl;
		number_face>>number;
		vector<vector<int>> myarray;
		//没有检测到一张人脸
		
		if(number > 0)
		{
			for(int i_2 = 0;i_2 < number;i_2++)
			{
				string line_location;
				getline(fDet,line_location);
				stringstream s_location(line_location);
				int x,y,w,h,sc;
				s_location>>x>>y>>w>>h>>sc;
				vector<int> my_array_1;
				my_array_1.push_back(x);
				my_array_1.push_back(y);
				my_array_1.push_back(w);
				my_array_1.push_back(h);
				my_array_1.push_back(sc);
				myarray.push_back(my_array_1);
				//cout<<x<<" "<<y<<" "<<w<<" "<<h<<" "<<sc<<endl;
			}
		}
		//int score_original = myarray[0][4];
		//处理标记的数据 需要去除第一行
		vector<string> f_annot;
		string line_annot;
		getline(fAnnot,line_annot);
		//从第二行开始保存读入的数据
		istringstream sin(line_annot);
		string filed;
		while(getline(sin,filed,','))
		{
			

			f_annot.push_back(filed);
		}

	
		string name = f_annot[0];
		string imS1_name_1 = f_annot[0];
		//比较两个名字是否一致，然后决定是否进入分数的判断环节
		if(name_det.compare(imS1_name_1)==0)
		{
			//先不处理多张人脸，值处理一张人脸的情况
			if(number == 0)
			{
				if(atoi(f_annot[1].c_str())==0\
					&&atoi(f_annot[2].c_str())==0&&\
					atoi(f_annot[3].c_str())==0 && \
					atoi(f_annot[4].c_str())==0)
				{
					double a = 1.0;
					double b = 1.0;
					Point2d s1;
					s1.x = a;
					s1.y = b;
					neg_neg.push_back(s1);
					myarray.clear();
					f_annot.clear();
					continue;
				}
				else
				{
					cout<<"hhahah"<<endl;
					Point2d sc_th_1;
					sc_th_1.x = double(10);
					sc_th_1.y = double(0);
					score_cal.push_back(sc_th_1);
					myarray.clear();
					f_annot.clear();
					continue;
				}
					
			}
			else
			{
				if(number!=0)
				{
					if(atoi(f_annot[1].c_str())==0&&\
						atoi(f_annot[2].c_str())==0	&& \
						atoi(f_annot[3].c_str())==0&& \
						atoi(f_annot[4].c_str())==0)
					{
						
						double a = 2.0;
						double b = 2.0;
						Point2d s1;
						s1.x = a;
						s1.y = b;
						neg_true.push_back(s1);
						myarray.clear();
						f_annot.clear();
						continue;

					}
				}
				number = 1;
				for(int n_f_index = 0;n_f_index < number;\
					n_f_index++)
				{
					//cout<<"名字匹配正确"<<endl;
					Mat img_det,img_annot;
					img_det = imread(im_name,0);
					img_annot = img_det.clone();
					//对于两张图像分别进行处理
					if(img_det.channels() > 1 || \
						img_annot.channels() > 1)
					{
						cout<<"输入图像的通道不正确"<<endl;
						exit(1);//强制退出，不正常的退出
					}
					//先处理检测的人脸图像
					int score_1;
					for(int i_r = 0;i_r < img_det.rows;i_r++)
					{
						for(int i_c = 0;i_c < img_det.cols;i_c++)
						{
							int x_1,y_1,width_1,height_1;
							x_1 = myarray[n_f_index][0];
							y_1 = myarray[n_f_index][1];
							width_1 = myarray[n_f_index][2];
							height_1 = myarray[n_f_index][3];
							score_1 = myarray[n_f_index][4];
							if(i_c >= x_1 && i_c <= (x_1 + \
								width_1)&&
								i_r >= y_1 && i_r <= (y_1 \
								+ height_1))
							{
								img_det.at<uchar>(i_r,i_c) = 0;
							}
							else
							{
								img_det.at<uchar>(i_r,i_c) = 90;
							}
						}
					}
					for(int i_r = 0;i_r < img_annot.rows;i_r++)
					{
						for(int i_c = 0;i_c < img_annot.cols;i_c++)
						{
							int x_1,y_1,x_2,y_2;
							x_1 = atoi(f_annot[1].c_str());
							x_1 < 0 ? 1:x_1;
							y_1 = atoi(f_annot[2].c_str());
							y_1 < 0 ? 1:y_1;
							x_2 = atoi(f_annot[3].c_str());
							x_2 < 0 ? 1:x_2;
							y_2 = atoi(f_annot[4].c_str());
							y_2 < 0 ? 1:y_2;
							if(i_c >= x_1 && i_c <= (x_2)&&\
								i_r >= y_1 && i_r <= (y_2))
							{
								img_annot.at<uchar>(i_r,i_c) = 0;
							}
							else
							{
								img_annot.at<uchar>(i_r,i_c) = 120;
							}
						}
					}
					IplImage* img_det_1 = &IplImage(img_det);
					IplImage* img_annot_1 = &IplImage(img_annot);

					double score_new;
					score_new = computeScore(img_det_1,img_annot_1);
					//cout<<"分数"<<endl;
					//cout<<score_new<<endl;
					Point2d sc_th;
					sc_th.x = score_new;
					sc_th.y = double(score_1);
					score_cal.push_back(sc_th);
				}
			}
		}
		myarray.clear();
		f_annot.clear();
	
	}
	
	fAnnot.close();
	fDet.close();
	//计算检测率
	vector<double> score_th_9;
	int neg_neg11 = neg_neg.size();
	int neg_true22 = neg_true.size();
	int neg_all = neg_neg11 + neg_true22;
	for(int i_3 = 0;i_3 < imNames->size() - neg_all;i_3++)
	{
		score_th_9.push_back(score_cal[i_3].y);
	}
	cout<<"know"<<endl;
	sort(score_th_9.begin(),score_th_9.end());
	score_th_9.reserve(score_th_9.size());
	
	vector<double>::iterator uniElem = unique(score_th_9.begin(),\
		score_th_9.end());
	score_th_9.erase(uniElem,score_th_9.end());
	//改变阈值后的情况
	ofstream result_rate(out_csv.c_str());
	for(vector<double>::iterator uit = score_th_9.begin();uit \
		!= score_th_9.end();++uit)
	{
		//cout<<"分数阈值"<<score_th_9[i]<<endl;
		double Th = (*uit)*0.01;
		int TPDisc = 0;
		int FN = 0;
		for(int i_4 = 0;i_4 < imNames->size() - neg_all;i_4++)
		{
			if(score_cal[i_4].x  > Th && score_cal[i_4].x <= 1.0 )
			{
				TPDisc++;
			}
			//这里的10是预先设定的
			if(score_cal[i_4].x == 10.0)
			{
				FN++;
			}
		}
		int neg_neg1 = neg_neg.size();
		int neg_true2 = neg_true.size();
		TPDisc = TPDisc + neg_neg1;
		double rate_face = (double)TPDisc / (double)(\
		imNames->size()!=0 ? imNames->size():1);
		cout<<"正确率"<<rate_face<<endl;
		cout<<"FN"<<(FN<0? 0:FN)<<endl;
		cout<<"误检"<<(neg_true2<0?0:neg_true2)<<endl;
		result_rate<<rate_face<<","<<((FN+neg_true2)<0? \
			0:(FN+neg_true2))<<","<<(Th*100)<<endl;
	}
	//cout<<"know"<<endl;
	result_rate.close();
	
	
	waitKey(0);
	system("pause");
	return 0;
}
