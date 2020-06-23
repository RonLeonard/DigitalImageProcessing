#include "Histogram1D.h"




Histogram1D::Histogram1D(): histSize(256)
{
	hranges[0] = 0.0f;
	hranges[1] = 255.0f;
	ranges[0] = hranges;
	channels = 0;
}

Histogram1D::~Histogram1D()
{

}



Mat Histogram1D::getHistogram(const Mat& image)
{
	Mat hist;
	
	calcHist(&image,// 要计算图像的
		1,                // 只计算一幅图像的直方图
		&channels,        // 通道数量
		Mat(),            // 不使用掩码
		hist,            // 存放直方图
		1,                // 1D直方图
		&histSize,        // 统计的灰度的个数
		ranges);        // 灰度值的范围

	return hist;
}



Mat Histogram1D::getHistogramImge(const Mat& image)
{
	Mat hist = getHistogram(image);

	double maxVal = 0.0;
	double minVal = 0;
	minMaxLoc(hist, &minVal, &maxVal);

	Mat histImg(histSize, histSize, CV_8U, Scalar(255, 255, 255));

	int hpt = static_cast<int>(0.9 * histSize);

	for (int h = 0; h < histSize; h++)
	{
		float binVal = hist.at<float>(h);
		int intensity = static_cast<int>(binVal * hpt / maxVal);
		line(histImg,
			Point(h, histSize),
			Point(h, histSize - intensity),
			Scalar::all(0));
	}

	return histImg;
}


void Histogram1D::histogram_equalize(const Mat& src, Mat& dst)
{
	Mat hist = getHistogram(src);
	hist /= (src.rows * src.cols);
	float cdf[256] = {0};
	Mat lut(1, 256, CV_8U);
	for (int i = 0; i < 256; i++)
	{
		if (i == 0)
			cdf[i] = hist.at<float>(i);
		else
			cdf[i] = cdf[i - 1] + hist.at<float>(i);
		lut.at<uchar>(i) = static_cast<uchar>(255 * cdf[i]);
	}
	LUT(src, lut, dst);
}


