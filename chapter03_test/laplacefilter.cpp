#define LAPLACE_FILTER
#ifdef LAPLACE_FILTER

#include <opencv.hpp>
#include <stdlib.h>
#include <stdio.h>

using namespace cv;

void laplace_filter(const Mat& src, Mat& dst)
{
	int window[9] = { 0, 1, 0, 1, -4, 1, 0, 1, 0 };
	for (int i = 1; i < src.rows -1 ; i++)
	{
		for (int j = 1; j < src.cols - 1; j++)
		{
			int idx = 0;
			int val = 0;
			for (int x = -1; x <= 1; x++)
			{
				for (int y = -1; y <= 1; y++)
				{
					val += src.at<uchar>(i + x, j + y) * window[idx++];
				}
			}
			dst.at<uchar>(i, j) = abs(val);
		}
	}
}


int main(int argc, char* argv[])
{
#define	USE_OPENCV_API
#ifdef USE_OPENCV_API
	Mat src, src_gray, dst_cv, abs_dst_cv;
	int kernel_size = 3;
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;
	const char* window_name1 = "dst_cv";
	const char* window_name2 = "dst";
	src = imread("pic/Laplace.jpg");
	if (!src.data)
	{
		std::cout << "read image failed." << std::endl;
		return -1;
	}

	GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);
	cvtColor(src, src_gray, CV_RGB2GRAY);
	namedWindow(window_name1, CV_WINDOW_AUTOSIZE);
	namedWindow(window_name2, CV_WINDOW_AUTOSIZE);
	Mat dst(src.size(), CV_8UC1, Scalar::all(0));
	laplace_filter(src_gray, dst);
	Laplacian(src_gray, dst_cv, ddepth, kernel_size, scale, delta, BORDER_DEFAULT);
	
	convertScaleAbs(dst_cv, abs_dst_cv);
	imshow(window_name1, abs_dst_cv);
	imshow(window_name2, dst);
	waitKey(0);
#endif



}
#endif