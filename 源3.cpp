//代码，在一张图片上打马赛克

#include <core\core.hpp>  
#include <highgui\highgui.hpp>  

using namespace cv;

int neightbourHoo = 9; //马赛克上每个方框的像素大小  

int main3()
{
	Mat image = imread("hat.png");
	Mat faceROI = image(Rect(100,100,200,200)); //兴趣区域不能显示？？

	
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
Point ptL; //左键按下时坐标  
Point ptR;  //右键按下时坐标  
			
void onMouse(int event, int x, int y, int flag, void *ustg);//鼠标回掉函数  

int main()
{
	imageSourceCopy = imread("hat.png");
	imageSource = imageSourceCopy.clone();
	//imshow("马赛克", imageSourceCopy);  
	namedWindow("马赛克");
	setMouseCallback("马赛克", onMouse);
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
		//对鼠标画出的矩形框超出图像范围做处理，否则会越界崩溃  
		x > imageSource.cols - 2 * neightbourHood ? x = imageSource.cols - 2 * neightbourHood : x = x;
		y > imageSource.rows - 2 * neightbourHood ? y = imageSource.rows - 2 * neightbourHood : y = y;

		//对鼠标从右下往右上画矩形框的情况做处理  
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
	imshow("马赛克", imageSourceCopy);
	waitKey();
}

*/