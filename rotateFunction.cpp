#include "rotateFunction.h"

void saveImage(Mat& image)
{
	string filename;
	cout << "Enter a name to save the image: ";
	getline(cin, filename);

	string outPath = "./rotated_" + filename + ".jpg";
	if (imwrite(outPath, image))
	{
		cout << "Image saved successfully as " << outPath << endl;
	}
	else
	{
		cout << "Error: Could not save the image." << endl;
	}
}

Mat rotateImage(int degree, Mat& originalImage)
{
	double radian = CV_PI * degree / 180.0;
	//double newCols = round(abs(originalImage.cols * cos(radian)) + abs(originalImage.rows * sin(radian)));
	double newCols = abs(originalImage.cols * cos(radian)) + abs(originalImage.rows * sin(radian));
	newCols = ceil((int)(newCols * 1000.0) % 1000 / 1000.0);	
	double newRows = round(abs(originalImage.rows * cos(radian)) + abs(originalImage.cols * sin(radian)));	
	Mat resultImage(newRows, newCols, originalImage.type());


	uchar* originalData = originalImage.data;
	uchar* resultData = resultImage.data;

	cout << "newRows: " << newRows << endl;
	cout << "newCols: " << newCols << endl;

	for (int row = 0; row < resultImage.rows; row++)
	{
		for (int col = 0; col < resultImage.cols; col++)
		{
			for (int i = 0; i < 3; i++)
			{
				resultData[row * resultImage.cols * 3 + col * 3 + i] = 0;
			}
		}
	}

	//입력 이미지에서 이미지 데이터를 interpolate하여 outputdata에 넣기
	for (int row = 0; row < resultImage.rows; row++)
	{
		for (int col = 0; col < resultImage.cols; col++)
		{

			double colPixel = (col - (resultImage.cols - 1) / 2.0) * cos(-radian) - (row - (resultImage.rows - 1) / 2.0) * sin(-radian) + (originalImage.cols - 1) / 2.0;
			double rowPixel = (col - (resultImage.cols - 1) / 2.0) * sin(-radian) + (row - (resultImage.rows - 1) / 2.0) * cos(-radian) + (originalImage.rows - 1) / 2.0;
			//rotate 한 outImage에서의 위치 구하기

			double rowWeight = abs(rowPixel - (int)rowPixel);
			double colWeight = abs(colPixel - (int)colPixel);

			for (int i = 0; i < 3; i++)
			{
				double sum = 0;

				if (ceil(rowPixel) == 0 && colPixel >= 0 && colPixel < originalImage.cols)
				{
					sum += (1 - colWeight) * originalData[static_cast<int>(ceil(rowPixel)) * originalImage.cols * 3 + static_cast<int>(floor(colPixel)) * 3 + i];
					sum += colWeight * originalData[static_cast<int>(ceil(rowPixel)) * originalImage.cols * 3 + static_cast<int>((colPixel)) * 3 + i];

					resultData[row * resultImage.cols * 3 + col * 3 + i] = round(sum);
				}
				else if (ceil(rowPixel) == originalImage.rows - 1 && colPixel >= 0 && colPixel < originalImage.cols)
				{
					sum += (1 - colWeight) * originalData[static_cast<int>(rowPixel) * originalImage.cols * 3 + static_cast<int>(colPixel) * 3 + i];
					sum += colWeight * originalData[static_cast<int>(rowPixel) * originalImage.cols * 3 + static_cast<int>(ceil(colPixel)) * 3 + i];

					resultData[row * resultImage.cols * 3 + col * 3 + i] = round(sum);
				}
				else if (rowPixel >= 0 && rowPixel < originalImage.rows && ceil(colPixel) == 0)
				{
					sum += (1 - rowWeight) * originalData[static_cast<int>(rowPixel) * originalImage.cols * 3 + static_cast<int>(ceil(colPixel)) * 3 + i];
					sum += rowWeight * originalData[static_cast<int>(ceil(rowPixel)) * originalImage.cols * 3 + static_cast<int>(ceil(colPixel)) * 3 + i];

					resultData[row * resultImage.cols * 3 + col * 3 + i] = round(sum);
				}
				else if (rowPixel >= 0 && rowPixel < originalImage.rows && floor(colPixel) == originalImage.cols - 1)
				{
					sum += (1 - rowWeight) * (1 - colWeight) * originalData[static_cast<int>(rowPixel) * originalImage.cols * 3 + static_cast<int>(colPixel) * 3 + i];
					sum += rowWeight * (1 - colWeight) * originalData[static_cast<int>(ceil(rowPixel)) * originalImage.cols * 3 + static_cast<int>(colPixel) * 3 + i];

					resultData[row * resultImage.cols * 3 + col * 3 + i] = round(sum);
				}
				else if (rowPixel > 0 && rowPixel < originalImage.rows  && colPixel > 0 && colPixel < originalImage.cols )
				{
					sum += (1 - rowWeight) * (1 - colWeight) * originalData[static_cast<int>(rowPixel) * originalImage.cols * 3 + static_cast<int>(colPixel) * 3 + i];
					sum += (1 - rowWeight) * colWeight * originalData[static_cast<int>(rowPixel) * originalImage.cols * 3 + static_cast<int>(ceil(colPixel)) * 3 + i];
					sum += rowWeight * (1 - colWeight) * originalData[static_cast<int>(ceil(rowPixel)) * originalImage.cols * 3 + static_cast<int>(colPixel) * 3 + i];
					sum += rowWeight * colWeight * originalData[static_cast<int>(ceil(rowPixel)) * originalImage.cols * 3 + static_cast<int>(ceil(colPixel)) * 3 + i];

					resultData[row * resultImage.cols * 3 + col * 3 + i] = round(sum);
				}
			}
		}
	}
	return resultImage;
}