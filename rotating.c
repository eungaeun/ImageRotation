#include <stdio.h>
#include <stdint.h>

typedef uint8_t  BYTE;

typedef struct
{
	BYTE  rgbtBlue;
	BYTE  rgbtGreen;
	BYTE  rgbtRed;
} __attribute__((__packed__))
RGBTRIPLE;

int main()
{

	RGBTRIPLE blurred_image[height][width];

	Mat image = imread("./pinggu.jpg", IMREAD_UNCHANGED);

	if (image.empty()) {
		cout << "Failed to load the image." << endl;
		return -1;
	}

	//resize ���߿� �Լ��� ��?
	int height = 450;
	int width = 600;

	Size targetSize(width, height);  // ��ǥ ũ�� ����

	Mat resizedImage;
	resize(image, resizedImage, targetSize);  // �̹��� ũ�� ����


	//// �̹��� ũ�� ��������
	//int width = image.cols;
	//int height = image.rows;
	Mat rotatedImage;
	for (int row = 0; row < width; row++)
	{
		uchar* pointer_row = image.ptr<uchar>(row);
		uchar* pointer_row_new = rotatedImage.ptr<uchar>(row);
		for (int col = 0; col < height; col++)
		{
			/*		uchar b = pointer_row[col * 3 + 0];
					uchar g = pointer_row[col * 3 + 1];
					uchar r = pointer_row[col * 3 + 2];
					printf("\t (%d, %d, %d)", r, g, b);*/
			pointer_row_new = pointer_row[col * 3 + 0];
		}

	}


	imshow("Original Image", resizedImage);

	waitKey(0);
	return 0;
}