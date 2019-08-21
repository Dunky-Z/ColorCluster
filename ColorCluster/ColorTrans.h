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
	ColorTrans();
	virtual ~ColorTrans() = default;
	void CalculateCenters(Mat& src, int nClusters, Mat& labels, Mat& centers, Vec3f *centersRGB);
	void ColorCluster(Mat& src, int nClusters, Mat& labels, Vec3f *centersRGB);
	vector<vector<int>> CalculateMinDistance(Mat& src, int nClusters, Vec3f* centersRGB);
	void ChangeColor(Mat& dst, int nClusters, vector<vector<int>>& label_src, vector<vector<int>>& label_dst, Vec3f* centersRGB);


public:
	double CalculateNorm(Vec3f p1, Vec3f p2)
	{
		double distance = sqrt((p1.val[0] - p2.val[0])*(p1.val[0] - p2.val[0]) + (p1.val[1] - p2.val[1])*(p1.val[1] - p2.val[1]) + (p1.val[2] - p2.val[2])*(p1.val[2] - p2.val[2]));
		return distance;
	}
};