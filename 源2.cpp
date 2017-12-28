#include <iostream>
#include <opencv2\opencv.hpp>

using namespace std;
using namespace cv;

int main1()
{
	Mat image = cv::imread("1.png");   //Ô­Í¼Ïñ²ÊÉ«Ã±×Ó
	
	Mat mask = cv::imread("hahh1.png");
	Mat dst=Mat::zeros(image.size(),image.type());
	imshow("image", image);
	imshow("mask", mask);
	imshow("d", dst);

	image.copyTo(dst, mask);

	imshow("dst", dst);
	imwrite("dst.png", dst);

	waitKey();
	return 0;
}

