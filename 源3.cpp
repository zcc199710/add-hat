//���룬��һ��ͼƬ�ϴ�������

#include <core\core.hpp>  
#include <highgui\highgui.hpp>  

using namespace cv;

int neightbourHoo = 9; //��������ÿ����������ش�С  

int main3()
{
	Mat image = imread("hat.png");
	Mat faceROI = image(Rect(100,100,200,200)); //��Ȥ��������ʾ����

	
	for (int i = 50; i < faceROI.rows- neightbourHoo; i += neightbourHoo)
	{
		for (int j = 0; j < faceROI.cols - neightbourHoo; j += neightbourHoo)
		{
			Mat roi = faceROI(Rect(j , i , neightbourHoo, neightbourHoo));

			Scalar sca = Scalar(
				faceROI.at<Vec3b>(i+2 ,j+2 )[0],
				faceROI.at<Vec3b>(i+2, j+2 )[1],
				faceROI.at<Vec3b>(i+2, j+2 )[2]);
			//Mat roiCopy = Mat(rect.size(), CV_8UC3, sca);
			//roiCopy.copyTo(roi);
			roi.setTo(sca);
		}
	}
	
	imshow("haha", faceROI);
	imshow("ha", image);
	waitKey(0);
	return 0;
}



/*
Point ptL; //�������ʱ����  
Point ptR;  //�Ҽ�����ʱ����  
			
void onMouse(int event, int x, int y, int flag, void *ustg);//���ص�����  

int main()
{
	imageSourceCopy = imread("hat.png");
	imageSource = imageSourceCopy.clone();
	//imshow("������", imageSourceCopy);  
	namedWindow("������");
	setMouseCallback("������", onMouse);
	waitKey();
}

void onMouse(int event, int x, int y, int flag, void *ustg)
{
	if (event == CV_EVENT_LBUTTONDOWN)
	{
		ptL = Point(x, y);
	}
	if (event == CV_EVENT_LBUTTONUP)
	{
		//����껭���ľ��ο򳬳�ͼ��Χ�����������Խ�����  
		x > imageSource.cols - 2 * neightbourHood ? x = imageSource.cols - 2 * neightbourHood : x = x;
		y > imageSource.rows - 2 * neightbourHood ? y = imageSource.rows - 2 * neightbourHood : y = y;

		//���������������ϻ����ο�����������  
		ptR = Point(x, y);
		Point pt = ptR;
		ptR.x < ptL.x ? ptR = ptL, ptL = pt : ptR = ptR;
		for (int i = 0; i < ptR.y - ptL.y; i += neightbourHood)
		{
			for (int j = 0; j < ptR.x - ptL.x; j += neightbourHood)
			{
				randomNum = rng.uniform(-neightbourHood / 2, neightbourHood / 2);
				Rect rect = Rect(j + neightbourHood + ptL.x, i + neightbourHood + ptL.y, neightbourHood, neightbourHood);
				Mat roi = imageSourceCopy(rect);
				Scalar sca = Scalar(
					imageSource.at<Vec3b>(i + randomNum + ptL.y, j + randomNum + ptL.x)[0],
					imageSource.at<Vec3b>(i + randomNum + ptL.y, j + randomNum + ptL.x)[1],
					imageSource.at<Vec3b>(i + randomNum + ptL.y, j + randomNum + ptL.x)[2]);
				//Mat roiCopy = Mat(rect.size(), CV_8UC3, sca);
				//roiCopy.copyTo(roi);
				roi.setTo(sca);
			}
		}
	}
	imshow("������", imageSourceCopy);
	waitKey();
}

*/