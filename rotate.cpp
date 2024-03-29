//c++ 헤더 파일
#include <iostream>
#include <stdlib.h>

// opencv 헤더 파일
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"
#include <opencv2/opencv.hpp>
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>

#include "rotateFunction.h"

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << "Usage:  programName.exe <imagePath> <degree> " << endl;
		return 1;
	}
	char* imagePath = argv[1];
	int rotationAngle = atoi(argv[2]);
	Mat inputImage = imread(imagePath, IMREAD_UNCHANGED);

	if (inputImage.empty()) {
		cout << "Failed to load the image." << endl;
		return 1;
	}

	Mat outImage = rotateImage(rotationAngle, inputImage);
		
	imshow("Original", inputImage);
	imshow("Rotated Image", outImage);
	saveImage(outImage);

	waitKey(0);
	return 0;
}