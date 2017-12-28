#include <iostream>
#include <opencv2\opencv.hpp>

using namespace std;
using namespace cv;

String face_cascade_name = "haarcascade_frontalface_alt2.xml";
CascadeClassifier face_cascade;
string window_name = "Capture - Face detection";
Mat frame;
Mat mask1 = imread("hahh.png");  //帽子区域为黑色，对roi进行抠图
Mat hat = imread("hat.png");  //直接加载  独立的 圣诞帽子  之后进行resize;

int neightbourHood = 20; //马赛克上每个方框的像素大小  


void detectAndDisplay(Mat frame)
{
	std::vector<Rect> faces;
	Mat frame_gray;

	cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
	equalizeHist(frame_gray, frame_gray);

	face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));
	for (size_t i = 0; i < faces.size(); i++)
	{
		//Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2);//人脸的中心点位置																						//ellipse( frame, center, Size( faces[i].width/2, faces[i].height/2), 0, 0, 360, Scalar( 255, 0, 255 ), 2, 8, 0 );
		//rectangle(frame, Point(faces[i].x, faces[i].y), Point(faces[i].x + faces[i].width, faces[i].y + faces[i].height), Scalar(255, 0, 255));
		Mat faceROI = frame(faces[i]);  //人脸矩阵框
		//imshow("face", faceROI);
		//waitKey(0);
		
	   //在这里加入添加帽子的代码
		int h = faceROI.cols * mask1.rows / mask1.cols; //resize 的  x 值 
		resize(mask1,mask1,Size(faceROI.cols, h));
		resize(hat, hat, Size(faceROI.cols, h));
		//考虑兴趣区域ke能出界的情况
		Mat Roi = frame(Rect(faces[i].x, faces[i].y - h+50, mask1.cols, mask1.rows)); //定义的兴趣区域

		//开始对 roi 和  进行掩码操作  留出空白
		Mat dst1 = Mat::zeros(Roi.size(), Roi.type());  //两个黑色的图片

		Roi.copyTo(dst1, mask1);   //目标区域应该有一个大空白
		dst1.copyTo(Roi);

		//之后两个区域进行相加 (roi +hat ) 黑色区域进行融合  

		Roi = Roi + hat;
		
		//对faceRoi进行处理 （加入马赛克）
		for (int si = 50; si < faceROI.rows - neightbourHood; si += neightbourHood)
		{
			for (int j = 0; j < faceROI.cols - neightbourHood; j += neightbourHood)
			{
				Mat roi = faceROI(Rect(j, si, neightbourHood, neightbourHood));

				Scalar sca = Scalar(
					faceROI.at<Vec3b>(si + 2, j + 2)[0],
					faceROI.at<Vec3b>(si + 2, j + 2)[1],
					faceROI.at<Vec3b>(si + 2, j + 2)[2]);
				//Mat roiCopy = Mat(rect.size(), CV_8UC3, sca);
				//roiCopy.copyTo(roi);
				roi.setTo(sca);
			}
		}
	
	}
	//-- 显示最终效果图
	imshow(window_name, frame);
	
}


int main()
{
	VideoCapture cap(0);
	Size size(cap.get(CV_CAP_PROP_FRAME_WIDTH), cap.get(CV_CAP_PROP_FRAME_HEIGHT));
	//VideoWriter writer("Video.avi", CV_FOURCC('M', 'J', 'P', 'G'), 25.0, size);
	VideoWriter writer("video.avi", CV_FOURCC('M', 'P', '4', '2'), 25, size);

	if (!face_cascade.load(face_cascade_name))
	{
		printf("--(!)Error loading ...\n");
		return -1;
	}
	while (1)
	{
		char key = waitKey(1);
		cap >> frame;
		
		if (!frame.empty())
		{
			detectAndDisplay(frame);
			writer << frame;
		}
		else
		{
			printf(" --(!) No captured frame -- Break!");
			continue;
		}

		if (key == 'q')
		{
			imwrite("me.png",frame);
		}
	}
	return 0;
}