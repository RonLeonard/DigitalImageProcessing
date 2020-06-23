//#define MEAN_FILTER
#ifdef MEAN_FILTER

#include <stdio.h>
#include<string.h>
#include "cv.h"
#include "highgui.h"

using namespace cv;


int getAverage(int* inputData, int dataSize)
{
	int sum = 0;
	int aver = 0;
	for (int k = 0; k < dataSize; k++)
		sum += inputData[k];
	aver = sum / dataSize;
	return aver;
}


int mean_filter(uchar* Buff, int w, int h)
{
	int mid = 0;
	int winsize = 3;
	int windows[9] = { 0 };
	uchar* cpBuff = new uchar[w * h];
	memcpy(cpBuff, Buff, w * h);
	int pos = (winsize - 1) / 2;
	int sum = 0;
	for (int i = pos; i < h - pos; i++)
	{
		for (int j = pos; j < w - pos; j++)
		{
			int winpos = 0;
			for (int m = -pos; m < winsize - pos; m++)
				for (int n = -pos; n < winsize - pos; n++)
					windows[winpos++] = cpBuff[(i + m) * w + (j + n)];
			
			mid = getAverage(windows, winsize * winsize);
			Buff[i * w + j] = mid;
		}
	}
	delete[] cpBuff;
	return 0;
}



int mean_filter(uchar* inBuf, int w, int h, uchar* outBuf)
{

	int mid = 0;
	int winsize = 3;
	int* windows = new int[winsize * winsize];
	int pos = (winsize - 1) / 2;
	memcpy(outBuf, inBuf, w * h);

	for (int m = pos; m < h - pos; m++)
	{
		for (int n = pos; n < w - pos; n++)
		{
			int winpos = 0;
			for (int i = -pos; i < (winsize - pos); i++)
				for (int j = -pos; j < (winsize - pos); j++)
					windows[winpos++] = inBuf[(m + i) * w + n + j];
			mid = getAverage(windows, winsize * winsize);
			outBuf[m * w + n] = mid;
		}
	}

	for (int k = 0; k < pos; k++)
		for (int l = pos; l < w - pos; l++)
			outBuf[k * w + l] = outBuf[pos * w + l];

	for (int a = h - pos; a < h; a++)
		for (int b = pos; b < w - pos; b++)
			outBuf[a * w + b] = outBuf[(h - pos - 1) * w + b];

	for (int c = 0; c < pos; c++)
		for (int d = 0; d < h; d++)
			outBuf[d * w + c] = outBuf[d * w + pos];

	for (int e = w - pos; e < w; e++)
		for (int f = 0; f < h; f++)
			outBuf[f * w + e] = outBuf[f * w + (w - pos - 1)];

	delete[] windows;
	windows = nullptr;
	return 0;
}



int main(int argc, char* argv)
{
#if 0// unit_test
	int windows[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int val = getAverage(windows, 9);
	printf("val = %d\n", val);

	cv::waitKey(0);
#endif

	Mat src = imread("mean_filter.bmp", 1);
	imshow("src", src);
	Mat src_gray(src.size(), CV_8UC1);
	cvtColor(src, src_gray, CV_RGB2GRAY);

	Mat noise(src.size(), CV_8UC1, Scalar::all(0));

	RNG rng(-1);
	//cvRandArr(&rng, &noise, CV_RAND_NORMAL, cvScalarAll(0), cvScalarAll(15));
	rng.fill(noise, CV_RAND_NORMAL, Scalar::all(0), Scalar::all(35));
	add(src_gray, noise, noise);
	
	imshow("noise", noise);

	mean_filter((uchar*)noise.data, noise.cols, noise.rows);
	imshow("mean_filter", noise);
	
	mean_filter((uchar*)src_gray.data, src_gray.cols, src_gray.rows);
	imshow("src_gray", src_gray);

	cvWaitKey(0);


	return 0;

}


#endif