//#define MEDIAN_FILTER
#ifdef MEDIAN_FILTER


#include <opencv.hpp>
#include <time.h>
using namespace cv;

void swap(uchar &a, uchar &b)
{
	uchar tmp;
	tmp = a;
	a = b;
	b = tmp;
}

#define WIN_SIZE 9
uchar calMedian(uchar win[WIN_SIZE])
{
	for (int gap = WIN_SIZE / 2; gap > 0; gap /= 2)
		for (int i = gap; i < WIN_SIZE; i++)
			for (int j = i - gap; j >= 0 && win[j] > win[j + gap]; j -= gap)
				swap(win[j], win[j + gap]);
	return win[WIN_SIZE / 2];
}



void salt(Mat& image, int num)
{
	if (image.empty())
	{
		std::cout << "image is empty!" << std::endl;
		return;
	}
	srand(time(NULL));
	int i, j;
	for (int k = 0; k < num; k++)
	{
		i = rand() % image.rows;
		j = rand() % image.cols;
		image.at<Vec3b>(i, j)[0] = 255;
		image.at<Vec3b>(i, j)[1] = 255;
		image.at<Vec3b>(i, j)[2] = 255;
	}
}


void median_filter(const Mat& src, Mat& dst)
{
	if (src.empty())
	{
		std::cout << "image is empty!" << std::endl;
		return;
	}

	Mat _dst(src.size(), src.type());
	int pos = 0;
	uchar win_0[WIN_SIZE] = { 0 };
	uchar win_1[WIN_SIZE] = { 0 };
	uchar win_2[WIN_SIZE] = { 0 };
	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			pos = 0;
			if ((i - 1) > 0 &&
				(i + 1) < src.rows &&
				(j - 1) > 0 &&
				(j + 1) < src.cols)
			{
				for (int m = i - 1; m <= i + 1; m++)
				{
					for (int n = j - 1; n <= j + 1; n++)
					{
						win_0[pos] = src.at<Vec3b>(m, n)[0];
						win_1[pos] = src.at<Vec3b>(m, n)[1];
						win_2[pos] = src.at<Vec3b>(m, n)[2];
						pos++;
					}
				}
				_dst.at<Vec3b>(i, j)[0] = calMedian(
					win_0);
				_dst.at<Vec3b>(i, j)[1] = calMedian(
					win_1);
				_dst.at<Vec3b>(i, j)[2] = calMedian(
					win_2);
			}
			else
				_dst.at<Vec3b>(i, j) = src.at<Vec3b>(i, j);
		}
	}
	_dst.copyTo(dst);
}


int main(int argc, char** argv)
{
	//test calMedian
	uchar win[9] = { 1, 5,  10 ,11, 18, 7, 8, 9 , 4};
	int ret = 0;
	ret = calMedian(win);
	printf("ret = %d\n", ret);


	Mat src, src_salt, dst, dst2;
	src = imread("pic/lenna.jpg");
	if (src.empty())
	{
		std::cout << "image is empty!" << std::endl;
		return -1;
	}
	imshow("src", src);
	
	salt(src, 300);
	imshow("src", src);
	median_filter(src, dst);
	imshow("dst", dst);
	medianBlur(src, dst2, 3);
	imshow("dst2", dst2);
	waitKey(0);
}


#endif