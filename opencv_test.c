#include <stdio.h>
#include "opencv/highgui.h"

int main() {

	IplImage* img = cvLoadImage("test.png");
	cvNamedWindow("test", CV_WINDOW_AUTOSIZE);
	cvShowImage("test", img);
	cvWaitKey(0);
	cvReleaseImage(&img);
	cvDestroyWindow("test");
}