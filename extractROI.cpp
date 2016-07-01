#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat img, temp;
Rect r;
bool drawing_box = false;

void onMouse(int event, int x, int y, int flags, void* param)
{
	switch(event)
	{
		case CV_EVENT_MOUSEMOVE : if(drawing_box)
									{
										r.width = x - r.x;
										r.height = y - r.y;
									}
									break;
		case CV_EVENT_LBUTTONDOWN : drawing_box = true;
									r = Rect(x, y, 0, 0);
									break;
		case CV_EVENT_LBUTTONUP : drawing_box = false;
									if(r.width < 0)
									{
										r.x += r.width;
										r.width *= -1;
									}
									if(r.height < 0)
									{
										r.y += r.height;
										r.height *= -1;
									}
									rectangle(temp, r, Scalar(255, 0, 0));
									break;
	}
}

int main(int argc, char** argv)
{
	img = imread(argv[1]);
	namedWindow("Select ROI");
	setMouseCallback("Select ROI", onMouse);
	temp = img.clone();
	while((char)waitKey(15) != 'a')
	{
		if(drawing_box)
		{
			temp = img.clone();
			rectangle(temp, r, Scalar(255, 0, 0));
		}
		imshow("Select ROI", temp);
	}
	cout << "\nRectangle (x, y) = (" << r.x << "," << r.y << ")  and (width, height) = (" << r.width << ", " << r.height << ")";   
	return 0;
}