#pragma once
#include<opencv2/core/core.hpp>  
#include<opencv2/highgui/highgui.hpp>  
#include <opencv2/highgui/highgui_c.h>
#include<opencv2/imgproc/imgproc.hpp>  
#include <algorithm>
#include<iostream>  
#include<string>  
#include <limits>

using namespace std;
using namespace cv;

class ColorTrans
{
public:
	const int nClusters = 8;	//设置提取颜色数

	ColorTrans();
	virtual ~ColorTrans() = default;
	void Test();
	void CalculateCenters(Mat& src, Mat& labels, Mat& centers, Vec3f *centersRGB);
	void ColorCluster(Mat& src, Mat& labels, const Vec3f *centersRGB);
	vector<vector<int>> CalculateMinDistance(const Mat& src, const Vec3f* centersRGB);
	void ChangeColorSelf(Mat& dst, const vector<vector<int>>& label_dst, const Vec3f* centersRGB);

public:
	double CalculateNorm(const Vec3f p1, const Vec3f p2)
	{
		double distance = sqrt((p1.val[0] - p2.val[0])*(p1.val[0] - p2.val[0]) + (p1.val[1] - p2.val[1])*(p1.val[1] - p2.val[1]) + (p1.val[2] - p2.val[2])*(p1.val[2] - p2.val[2]));
		return distance;
	}
};