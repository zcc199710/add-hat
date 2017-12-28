#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
using namespace cv;
using namespace std; 


int g_nThresholdValue = 100;
int g_nThresholdType = 3;
Mat g_srcImage, g_grayImage, g_dstImage;


void on_Threshold(int, void*);//回调函数

int main2()
{
	//【1】读入源图片
	g_srcImage = imread("1.png");
	if (!g_srcImage.data) { printf("读取图片错误，请确定目录下是否有imread函数指定的图片存在~！ \n"); return false; }
	imshow("原始图", g_srcImage);

	//【2】存留一份原图的灰度图
	cvtColor(g_srcImage, g_grayImage, COLOR_RGB2GRAY);

	//【3】创建窗口并显示原始图

	//【4】创建滑动条来控制阈值
	createTrackbar("模式",
		"原始图", &g_nThresholdType,
		4, on_Threshold);

	createTrackbar("参数值",
		"原始图", &g_nThresholdValue,
		255, on_Threshold);

	//【5】初始化自定义的阈值回调函数
	on_Threshold(0, 0);

	// 【6】轮询等待用户按键，如果ESC键按下则退出程序
	while (1)
	{
		char key;
		key = waitKey(20);
		if (key == 'p') { imwrite("hahh.png", g_dstImage); }
	}

}

void on_Threshold(int, void*)
{
	//调用阈值函数
	threshold(g_grayImage, g_dstImage, g_nThresholdValue, 255, g_nThresholdType);

	//更新效果图
	imshow("效果图", g_dstImage);
}
