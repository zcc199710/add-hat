#include <iostream>
#include <opencv2\opencv.hpp>

using namespace std;
using namespace cv;

String face_cascade_name = "haarcascade_frontalface_alt2.xml";
CascadeClassifier face_cascade;
string window_name = "Capture - Face detection";
Mat frame;
Mat mask1 = imread("hahh.png");  //ñ������Ϊ��ɫ����roi���п�ͼ
Mat hat = imread("hat.png");  //ֱ�Ӽ���  ������ ʥ��ñ��  ֮�����resize;

int neightbourHood = 20; //��������ÿ����������ش�С  


void detectAndDisplay(Mat frame)
{
	std::vector<Rect> faces;
	Mat frame_gray;

	cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
	equalizeHist(frame_gray, frame_gray);

	face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));
	for (size_t i = 0; i < faces.size(); i++)
	{
		//Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2);//���������ĵ�λ��																						//ellipse( frame, center, Size( faces[i].width/2, faces[i].height/2), 0, 0, 360, Scalar( 255, 0, 255 ), 2, 8, 0 );
		//rectangle(frame, Point(faces[i].x, faces[i].y), Point(faces[i].x + faces[i].width, faces[i].y + faces[i].height), Scalar(255, 0, 255));
		Mat faceROI = frame(faces[i]);  //���������
		//imshow("face", faceROI);
		//waitKey(0);
		
	   //������������ñ�ӵĴ���
		int h = faceROI.cols * mask1.rows / mask1.cols; //resize ��  x ֵ 
		resize(mask1,mask1,Size(faceROI.cols, h));
		resize(hat, hat, Size(faceROI.cols, h));
		//������Ȥ����ke�ܳ�������
		Mat Roi = frame(Rect(faces[i].x, faces[i].y - h+50, mask1.cols, mask1.rows)); //�������Ȥ����

		//��ʼ�� roi ��  �����������  �����հ�
		Mat dst1 = Mat::zeros(Roi.size(), Roi.type());  //������ɫ��ͼƬ

		Roi.copyTo(dst1, mask1);   //Ŀ������Ӧ����һ����հ�
		dst1.copyTo(Roi);

		//֮���������������� (roi +hat ) ��ɫ��������ں�  

		Roi = Roi + hat;
		
		//��faceRoi���д��� �����������ˣ�
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
	//-- ��ʾ����Ч��ͼ
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