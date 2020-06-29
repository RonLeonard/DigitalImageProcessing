#define SOBELFILTER
#ifdef SOBELFILTER

#include <opencv.hpp>
#include <iostream>

using namespace cv;


void sobel_filter_x(const Mat &src, Mat &dst)
{
	int window[9] = { -1, 0, 1, -2, 0, 2, -1, 0, 1 } ;
	for (int i = 1; i < src.rows - 1; i++)
	{
		for (int j = 1; j < src.cols - 1; j++)
		{
			int idx = 0;
			int val = 0;
			for (int x = -1; x <= 1; x++)
			{
				for (int y = -1; y <= 1; y++)
				{
					val += src.at<uchar>(i + x, j + y) * window[idx];
					idx++;
				}
			}
			dst.at<uchar>(i, j) = abs(val);
		}
	}
}



void sobel_filter_y(const Mat& src, Mat& dst)
{
	int window[9] = { -1, -2, -1, 0, 0, 0, 1, 2, 1 };
	for (int i = 1; i < src.rows - 1; i++)
	{
		for (int j = 1; j < src.cols - 1; j++)
		{
			int idx = 0;
			int val = 0;
			for (int x = -1; x <= 1; x++)
			{
				for (int y = -1; y <= 1; y++)
				{
					val += src.at<uchar>(i + x, j + y) * window[idx];
					idx++;
				}
			}
			dst.at<uchar>(i, j) = abs(val);
		}
	}
}


void sobel_filter(const Mat& src, Mat& dst)
{
	int window_x[9] = { -1, -2, -1, 0, 0, 0, 1, 2, 1 };
	int window_y[9] = { -1, 0, 1, -2, 0, 2, -1, 0, 1 };
	for (int i = 1; i < src.rows - 1; i++)
	{
		for (int j = 1; j < src.cols - 1; j++)
		{
			int idx1 = 0, idx2 = 0;
			int dst_x = 0 , dst_y = 0;
			for (int x = -1; x <= 1; x++)
			{
				for (int y = -1; y <= 1; y++)
				{
					dst_x += src.at<uchar>(i + x, j + y) * window_x[idx1];
					idx1++;
				}
			}

			for (int x = -1; x <= 1; x++)
			{
				for (int y = -1; y <= 1; y++)
				{
					dst_y += src.at<uchar>(i + x, j + y) * window_y[idx2];
					idx2++;
				}
			}
			dst.at<uchar>(i, j) = sqrt(pow(dst_x, 2) + pow(dst_y, 2));
		}
	}
}

int main(int argc, char* argv[])
{
	
	Mat img = imread("pic/lenna.jpg", 0);
	if (img.empty())
	{
		std::cout << "read picture failed" << std::endl;
		return -1;
	}
	imshow("img", img);
	Mat img_sobel_x(img.size(), CV_8UC1, Scalar::all(0));
	Mat img_sobel_y(img.size(), CV_8UC1, Scalar::all(0));
	Mat img_sobel(img.size(), CV_8UC1, Scalar::all(0));

	sobel_filter_x(img, img_sobel_x);
	sobel_filter_y(img, img_sobel_y);
	sobel_filter(img, img_sobel);

	imshow("sobel_x", img_sobel_x);
	imshow("sobel_y", img_sobel_y);
	imshow("sobel", img_sobel);


	Mat grad_x, grad_y, abs_grad_x, abs_grad_y, dstImage;
	Sobel(img, grad_x, CV_16S, 1, 0, 3, 1, 1, BORDER_DEFAULT);
	convertScaleAbs(grad_x, abs_grad_x);

	Sobel(img, grad_y, CV_16S, 0, 1, 3, 1, 1, BORDER_DEFAULT);
	convertScaleAbs(grad_y, abs_grad_y);
	imshow("abs_grad_x", abs_grad_x);
	imshow("abs_grad_y", abs_grad_y);

	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dstImage);
	imshow("dstImage", dstImage);
	waitKey(0);
	return 0;
}

#endif