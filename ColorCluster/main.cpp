#include "ColorTrans.h"

int main()
{
	ColorTrans colorTrans;
	const int nClusters = 8;	//设定提取颜色数

	Mat srcImage = imread("sichou.bmp");
	int nRows = srcImage.rows;
	int nCols = srcImage.cols;
	Mat centers(nClusters, 1, CV_32FC3);
	Mat labels(nRows*nCols, 1, CV_8UC1);
	Vec3f *centersRGB = new Vec3f[nClusters];

	Mat dstImage = imread("circle.png");
	int nRowsdst = dstImage.rows;
	int nColsdst = dstImage.cols;
	Mat centers_dst(nClusters, 1, CV_32FC3);
	Mat labels_dst(nRowsdst*nColsdst, 1, CV_8UC1);
	Vec3f *centersRGB_dst = new Vec3f[nClusters];

	//namedWindow("dstsrc", CV_WINDOW_NORMAL);
	//imshow("dstsrc", dstImage);
	cout << "1" << endl;
	colorTrans.CalculateCenters(srcImage, labels, centers, centersRGB);
	cout << "2" << endl;
	colorTrans.CalculateCenters(dstImage, labels_dst, centers_dst, centersRGB_dst);
	//colorTrans.ColorCluster(srcImage, labels, centersRGB);
	vector<vector<int>> label_src = colorTrans.CalculateMinDistance(srcImage, centersRGB);
	vector<vector<int>> label_dst = colorTrans.CalculateMinDistance(dstImage, centersRGB_dst);
	colorTrans.ChangeColorSelf(dstImage, label_dst, centersRGB);
	//waitKey(0);
	//destroyAllWindows();
	return 0;

}



