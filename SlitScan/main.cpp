#include<opencv2/core.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/videoio.hpp>
#include<opencv2/highgui.hpp>

#include<iostream>
#include<string>
#include<iomanip>
#include<sstream>

using namespace::std;
using namespace::cv;

int main()
{
	VideoCapture capt(0);

	int deviceID = 0;
	int apiID = cv::CAP_ANY;

	capt.open(deviceID, apiID);

	if (!capt.isOpened())
	{
		cout << "could not open camera " << endl;
		return -1;
	}

	Mat frame;
	capt.read(frame);
	int rows = frame.rows;
	int cols = frame.cols;

	Mat zero = cv::Mat::zeros(rows, cols, frame.type());
	Point start = Point(0, 0);
	Point end = Point(cols, 0);
	Scalar color = Scalar(0, 0, 200);

	for (int i = 0; i < rows; i++)
	{
		capt.read(frame);
	
		frame.row(i).copyTo(zero.row(i));

		if (i == 0)
		{
			zero.row(0).copyTo(frame.row(0));
		}
		else
		{
			zero.rowRange(0,i).copyTo(frame.rowRange(0,i));
		}

		start.y = i;
		end.y = i; 

		line(frame, start, end, color, 2, LINE_8);
		
		imshow("live", frame);
		waitKey(1);
	}

	return 0;
}
