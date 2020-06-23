#ifndef HISTOGRAM1D_H_
#define HISTOGRAM1D_H_

#include <opencv.hpp>
using namespace cv;
class Histogram1D
{
public:
	Histogram1D();
	~Histogram1D();
	Mat getHistogram(const Mat &image);
	Mat getHistogramImge(const Mat& image);
	void histogram_equalize(const Mat& src, Mat& dst);
private:
	int histSize;
	float hranges[2];
	const float* ranges[1];
	int channels;
};

#endif