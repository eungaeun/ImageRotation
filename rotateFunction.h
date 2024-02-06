#ifndef ROTATE_H
#define ROTATE_H

#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"
#include <opencv2/opencv.hpp>
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace cv;
using namespace std;

void saveImage(Mat& image);
Mat rotateImage(int degree, Mat& originalImage);

#endif