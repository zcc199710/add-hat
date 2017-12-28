#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
using namespace cv;
using namespace std; 


int g_nThresholdValue = 100;
int g_nThresholdType = 3;
Mat g_srcImage, g_grayImage, g_dstImage;


void on_Threshold(int, void*);//�ص�����

int main2()
{
	//��1������ԴͼƬ
	g_srcImage = imread("1.png");
	if (!g_srcImage.data) { printf("��ȡͼƬ������ȷ��Ŀ¼���Ƿ���imread����ָ����ͼƬ����~�� \n"); return false; }
	imshow("ԭʼͼ", g_srcImage);

	//��2������һ��ԭͼ�ĻҶ�ͼ
	cvtColor(g_srcImage, g_grayImage, COLOR_RGB2GRAY);

	//��3���������ڲ���ʾԭʼͼ

	//��4��������������������ֵ
	createTrackbar("ģʽ",
		"ԭʼͼ", &g_nThresholdType,
		4, on_Threshold);

	createTrackbar("����ֵ",
		"ԭʼͼ", &g_nThresholdValue,
		255, on_Threshold);

	//��5����ʼ���Զ������ֵ�ص�����
	on_Threshold(0, 0);

	// ��6����ѯ�ȴ��û����������ESC���������˳�����
	while (1)
	{
		char key;
		key = waitKey(20);
		if (key == 'p') { imwrite("hahh.png", g_dstImage); }
	}

}

void on_Threshold(int, void*)
{
	//������ֵ����
	threshold(g_grayImage, g_dstImage, g_nThresholdValue, 255, g_nThresholdType);

	//����Ч��ͼ
	imshow("Ч��ͼ", g_dstImage);
}
