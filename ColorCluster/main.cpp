#include "ColorTrans.h"

int main()
{
	ColorTrans colorTrans;
	int nClusters = 20;
	Mat srcImage = imread("sichou.bmp");
	int nRows = srcImage.rows;
	int nCols = srcImage.cols;
	Mat centers(nClusters, 1, CV_32FC3);
	Mat labels(nRows*nCols, 1, CV_8UC1);
	Vec3f *centersRGB = new Vec3f[nClusters];

	colorTrans.CalculateCenters(srcImage, nClusters, labels, centers, centersRGB);
	colorTrans.ColorCluster(srcImage, nClusters, labels, centersRGB);
	return 0;
}



