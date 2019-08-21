#include "ColorTrans.h"

ColorTrans::ColorTrans()
{
}

//����ɫ������ɫ����ͬ�����Ƚ�������
bool cmp(const Vec3f & x, const Vec3f & y)
{
	if (x.val[0] != y.val[0])
		return x.val[0] < y.val[0];
	else
		return x.val[2] > y.val[2];
}

void ColorTrans::CalculateCenters(Mat & src, int nClusters, Mat& labels, Mat& centers, Vec3f *centersRGB)
{

	if (!src.data)
	{
		return;
	}

	//�ָ�ͨ��
	vector<Mat> bgr;
	split(src, bgr);

	int nRows = src.rows;
	int nCols = src.cols;

	//�������� ���д洢
	Mat samples(nRows*nCols, 1, CV_32FC3);

	for (int i = 0; i < nRows; ++i)
	{
		for (int j = 0; j < nCols; ++j)
		{
			for (int iChanel = 0; iChanel < 3; ++iChanel)
			{
				samples.at<Vec3f>(i*nCols + j)[iChanel] = bgr[iChanel].at<uchar>(i, j);
			}
		}
	}

	TermCriteria  criteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 100, FLT_EPSILON);

	//���о���
	kmeans(samples, nClusters, labels, criteria, 1, KMEANS_PP_CENTERS, centers);

	//ÿ��������ɫ����
	cout << "��ɫ��������" << endl;
	for (int i = 0; i < nClusters; ++i)
	{
		centersRGB[i] = centers.ptr<Vec3f>(i)[0];
	}
}


void ColorTrans::ColorCluster(Mat& src, int nClusters, Mat& labels, Vec3f * centersRGB)
{
	int nRows = src.rows;
	int nCols = src.cols;
	//int dis = nRows / nClusters;
	//for (int i = 0; i < nClusters; ++i)
	//{
	//	for (int r = i * dis; r < (i + 1)*dis; ++r)
	//	{
	//		for (int c = 0; c < nCols; ++c)
	//		{
	//			*res.ptr<Vec3b>(r, c) = p[i];
	//		}
	//	}
	//}

	Mat restmp(nClusters, 1, CV_8UC3);
	for (int r = 0; r < nClusters; ++r)
	{
		*restmp.ptr<Vec3b>(r, 0) = centersRGB[r];
	}
	Mat resHSL(nClusters, 1, CV_8UC3);

	cvtColor(restmp, resHSL, COLOR_BGR2HSV);

	cout << "��ɫ��������" << endl;
	Vec3f *q = new Vec3f[nClusters];
	for (int i = 0; i < nClusters; ++i)
	{
		q[i] = resHSL.ptr<Vec3b>(i)[0];
		//cout << q[i].val[0] <<" "<< (double)q[i].val[1] << " "<< (double)q[i].val[2] << endl;
	}

	//ɫ������
	sort(q, q + nClusters, cmp);
	for (int i = 0; i < nClusters; ++i)
	{
		cout << q[i] << endl;
		//cout << q[i].val[0] <<" "<< (double)q[i].val[1] << " "<< (double)q[i].val[2] << endl;
	}

	//�ָ�����ɫ
	Mat res(nRows, nCols, CV_8UC3);

	//���ɫ��
	int dis = nRows / nClusters;
	for (int i = 0; i < nClusters; ++i)
	{
		for (int r = i * dis; r < (i + 1)*dis; ++r)
		{
			for (int c = 0; c < nCols; ++c)
			{
				*res.ptr<Vec3b>(r, c) = q[i];
			}
		}
	}
	//ת��RGB�ռ�
	cvtColor(res, res, COLOR_HSV2BGR);

	namedWindow("ԭͼ��", CV_WINDOW_NORMAL);
	imshow("ԭͼ��", src);
	namedWindow("ɫ��", CV_WINDOW_NORMAL);
	imshow("ɫ��", res);

	//ÿ�������ռ�ı���
	float* precent = new float[nClusters];
	memset(precent, 0, sizeof(centersRGB)*nClusters);

	for (int n = 0; n < nRows*nCols; ++n)
	{
		int r = n / nCols;
		int c = n % nCols;

		*res.ptr<Vec3b>(r, c) = centersRGB[*labels.ptr<uchar>(n, 0)];
		precent[*labels.ptr<uchar>(n, 0)] ++;
	}

	cout << "��Ӧ��ɫ����" << endl;
	for (int i = 0; i < nClusters; ++i)
	{
		precent[i] /= (nRows*nCols);
		cout << precent[i] << " ";
	}
	cout << endl;
}

vector<vector<int>> ColorTrans::CalculateMinDistance(Mat& src, int nClusters, Vec3f* centersRGB)
{

	int nRows = src.rows;
	int nCols = src.cols;
	vector<vector<int>> label(nRows, vector<int>(nCols, 0));

	int l;

	for (int i = 0; i < nRows; ++i)
	{
		for (int j = 0; j < nCols; ++j)
		{
			Vec3f p;
			p.val[0] = src.at<Vec3b>(i, j)[0];
			p.val[1] = src.at<Vec3b>(i, j)[1];
			p.val[2] = src.at<Vec3b>(i, j)[2];
			double minDis = DBL_MAX;
			for (int k = 0; k < nClusters; ++k)
			{
				Vec3f pp = centersRGB[k];
				double t = CalculateNorm(p, pp);
				if (t < minDis)
				{
					minDis = t;
					l = k;
				}
			}
			label[i][j] = l;
			//cout << label[i][j] << " ";
		}
		//cout << endl;
	}
	return label;
}

void ColorTrans::ChangeColor(Mat& dst, int nClusters, vector<vector<int>>& label_src, vector<vector<int>>& label_dst, Vec3f* centersRGB)
{
	int nRows = dst.rows;
	int nCols = dst.cols;
	int index = 2;
	for (int i = 0; i < nRows; ++i)
	{
		for (int j = 0; j < nCols; ++j)
		{
			for (int k = 0; k < nClusters; ++k)
			{
				if (label_dst[i][j] == k)
				{
					dst.at<Vec3b>(i, j)[0] = centersRGB[(k + index) % 10].val[0];
					dst.at<Vec3b>(i, j)[1] = centersRGB[(k + index) % 10].val[1];
					dst.at<Vec3b>(i, j)[2] = centersRGB[(k + index) % 10].val[2];
				}
			}
		}
	}
	namedWindow("�滻��", CV_WINDOW_NORMAL);
	imshow("�滻��", dst);
}
