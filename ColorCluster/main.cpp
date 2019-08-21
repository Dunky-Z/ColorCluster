#include "ColorTrans.h"

int main()
{
	ColorTrans colorTrans;
	int nClusters = 36;	//设定提取颜色数
	Mat srcImage = imread("sichou.tif");
	int nRows = srcImage.rows;
	int nCols = srcImage.cols;
	Mat centers(nClusters, 1, CV_32FC3);
	Mat labels(nRows*nCols, 1, CV_8UC1);
	Vec3f *centersRGB = new Vec3f[nClusters];

	colorTrans.CalculateCenters(srcImage, nClusters, labels, centers, centersRGB);
	colorTrans.ColorCluster(srcImage, nClusters, labels, centersRGB);
	vector<vector<int>> label_src = colorTrans.CalculateMinDistance(srcImage, nClusters, centersRGB);
	vector<vector<int>> label_dst = colorTrans.CalculateMinDistance(srcImage, nClusters, centersRGB);
	colorTrans.ChangeColor(srcImage, nClusters,label_src, label_dst, centersRGB);
	waitKey(0);
	return 0;
}



