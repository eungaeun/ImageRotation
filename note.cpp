////c++ 헤더 파일
//#include <iostream>
//#include <stdlib.h>
//
//// opencv 헤더 파일
//#include "opencv2/highgui.hpp"
//#include "opencv2/core.hpp"
//#include <opencv2/opencv.hpp>
//#include <cmath>
//#define _USE_MATH_DEFINES
//#include <math.h>
//
//using namespace cv;
//using namespace std;
//
//void saveImage(Mat& image);
//Mat rotateImage(int degree, Mat& originalImage);
//
//int main(int argc, char* argv[])
//{
//	if (argc != 3)
//	{
//		cout << "Usage:  programName.exe <imagePath> <degree> " << endl;
//		return 1;
//	}
//	char* imagePath = argv[1];
//	int rotationAngle = atoi(argv[2]);
//	Mat inputImage = imread(imagePath, IMREAD_UNCHANGED);
//
//	if (inputImage.empty()) {
//		cout << "Failed to load the image." << endl;
//		return 1;
//	}
//
//	Mat outImage = rotateImage(rotationAngle, inputImage);
//
//	imshow("Original", inputImage);
//	imshow("Rotated Image", outImage);
//	saveImage(outImage);
//
//	waitKey(0);
//	return 0;
//}
//
//void saveImage(Mat& image)
//{
//	string filename;
//	cout << "Enter a name to save the image: ";
//	getline(cin, filename);
//
//	string outPath = "./rotated_" + filename + ".jpg";
//	if (imwrite(outPath, image))
//	{
//		cout << "Image saved successfully as " << outPath << endl;
//	}
//	else
//	{
//		cout << "Error: Could not save the image." << endl;
//	}
//}
//
//Mat rotateImage(int degree, Mat& originalImage)
//{
//	double radian = M_PI * degree / 180.0;
//	//double radian = 3.141592 * degree / 180.0;
//	int newRows = ceil(abs(originalImage.rows * cos(radian)) + abs(originalImage.cols * sin(radian)));
//	int newCols = ceil(abs(originalImage.cols * cos(radian)) + abs(originalImage.rows * sin(radian)));
//	Mat resultImage(newRows, newCols, originalImage.type());
//
//	uchar* originalData = originalImage.data;
//	uchar* resultData = resultImage.data;
//
//	//resultImage 초기화
//	for (int row = 0; row < resultImage.rows; row++)
//	{
//		for (int col = 0; col < resultImage.cols; col++)
//		{
//			for (int i = 0; i < 3; i++)
//			{
//				resultData[row * resultImage.cols * 3 + col * 3 + i] = 0;
//			}
//		}
//	}
//
//	//입력 이미지에서 이미지 데이터를 interpolate하여 outputdata에 넣기
//	for (int row = 0; row < resultImage.rows; row++)
//	{
//		for (int col = 0; col < resultImage.cols; col++)
//		{
//			//rotate 한 outImage에서의 위치 구하기 (회전 행렬과의 곱셈 나중에 구현)
//			double outRowPixel = (row - (resultImage.rows / 2)) * cos(-radian) - (col - (resultImage.cols / 2)) * sin(-radian) + (originalImage.rows / 2);
//			double outColPixel = (row - (resultImage.rows / 2)) * sin(-radian) + (col - (resultImage.cols / 2)) * cos(-radian) + (originalImage.cols / 2);
//
//			//calculate weight
//			double rowWeight = static_cast<int>(outRowPixel * 1000) % 1000 / 1000.0;
//			double colWeight = static_cast<int>(outColPixel * 1000) % 1000 / 1000.0;
//
//			//if (col == 0 || col == resultImage.cols - 1)
//			//{
//			//	cout << "(row, col) =  (" << row << ", " << col << ")" << endl;
//			//	cout << "(outRowPixel, outColPixel) =  (" << outRowPixel << ", " << outColPixel << ")" << endl;
//			////	cout << "(rowWeight, colWeight) =  (" << rowWeight << ", " << colWeight << ")" << endl;
//			//	cout << endl;
//			//}
//
//
//			for (int i = 0; i < 3; i++)
//			{
//				double sum = 0;
//
//				if (ceil(outRowPixel) == 0 && outColPixel >= 0 && outColPixel < originalImage.cols)
//				{
//					sum += (1 - colWeight) * originalData[static_cast<int>(ceil(outRowPixel)) * originalImage.cols * 3 + static_cast<int>(outColPixel) * 3 + i];
//					sum += colWeight * originalData[static_cast<int>(ceil(outRowPixel)) * originalImage.cols * 3 + static_cast<int>(ceil(outColPixel)) * 3 + i];
//
//					resultData[row * resultImage.cols * 3 + col * 3 + i] = round(sum);
//				}
//				else if (floor(outRowPixel) == originalImage.rows - 1 && outColPixel >= 0 && outColPixel < originalImage.cols)
//				{
//					sum += (1 - colWeight) * originalData[static_cast<int>(outRowPixel) * originalImage.cols * 3 + static_cast<int>(outColPixel) * 3 + i];
//					sum += colWeight * originalData[static_cast<int>(outRowPixel) * originalImage.cols * 3 + static_cast<int>(ceil(outColPixel)) * 3 + i];
//
//					resultData[row * resultImage.cols * 3 + col * 3 + i] = round(sum);
//				}
//				else if (outRowPixel >= 0 && outRowPixel < originalImage.rows && ceil(outColPixel) == 0)
//				{
//					sum += (1 - rowWeight) * originalData[static_cast<int>(outRowPixel) * originalImage.cols * 3 + static_cast<int>(ceil(outColPixel)) * 3 + i];
//					sum += rowWeight * originalData[static_cast<int>(ceil(outRowPixel)) * originalImage.cols * 3 + static_cast<int>(ceil(outColPixel)) * 3 + i];
//
//					resultData[row * resultImage.cols * 3 + col * 3 + i] = round(sum);
//				}
//				else if (outRowPixel >= 0 && outRowPixel < originalImage.rows && floor(outColPixel) == originalImage.cols - 1)
//				{
//					sum += (1 - rowWeight) * (1 - colWeight) * originalData[static_cast<int>(outRowPixel) * originalImage.cols * 3 + static_cast<int>(outColPixel) * 3 + i];
//					sum += rowWeight * (1 - colWeight) * originalData[static_cast<int>(ceil(outRowPixel)) * originalImage.cols * 3 + static_cast<int>(outColPixel) * 3 + i];
//
//					resultData[row * resultImage.cols * 3 + col * 3 + i] = round(sum);
//				}
//				else if (outRowPixel >= 0 && outRowPixel < originalImage.rows && outColPixel >= 0 && outColPixel < originalImage.cols)
//				{
//					sum += (1 - rowWeight) * (1 - colWeight) * originalData[static_cast<int>(outRowPixel) * originalImage.cols * 3 + static_cast<int>(outColPixel) * 3 + i];
//					sum += (1 - rowWeight) * colWeight * originalData[static_cast<int>(outRowPixel) * originalImage.cols * 3 + static_cast<int>(ceil(outColPixel)) * 3 + i];
//					sum += rowWeight * (1 - colWeight) * originalData[static_cast<int>(ceil(outRowPixel)) * originalImage.cols * 3 + static_cast<int>(outColPixel) * 3 + i];
//					sum += rowWeight * colWeight * originalData[static_cast<int>(ceil(outRowPixel)) * originalImage.cols * 3 + static_cast<int>(ceil(outColPixel)) * 3 + i];
//
//					resultData[row * resultImage.cols * 3 + col * 3 + i] = round(sum);
//				}
//			}
//		}
//	}
//	return resultImage;
//}