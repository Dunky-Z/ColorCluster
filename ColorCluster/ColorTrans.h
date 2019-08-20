#pragma once
#include<opencv2/core/core.hpp>  
#include<opencv2/highgui/highgui.hpp>  
#include <opencv2/highgui/highgui_c.h>
#include<opencv2/imgproc/imgproc.hpp>  
#include <algorithm>
#include<iostream>  
#include<string>  

using namespace std;
using namespace cv;

class ColorTrans
{
public:
	ColorTrans();
	virtual ~ColorTrans() = default;
	void CalculateCenters(Mat& src, int nClusters,Mat labels, Mat centers, Vec3f *centersRGB);
	void ColorCluster(Mat& src, int nClusters, Mat labels, Vec3f *centersRGB);
};