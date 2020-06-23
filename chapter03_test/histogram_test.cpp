//#define HISTOGRAM

#ifdef HISTOGRAM

#include <iostream>
#include <opencv.hpp>
#include "Histogram1D.h"

using namespace cv;


Mat histogramCal(const Mat& image)
{
    int histSize = 256;                //直方图的最大像素值
    float range[] = { 0, 255 };
    const float* histRange = { range };
    vector<Mat> bgr(3);                   //存储图像的矩阵
    split(image, bgr);                 //将彩色图像分割成，b,g,r分别存储
    Mat b_hist, g_hist, r_hist;
    //分别计算各个波段的直方图
    calcHist(&bgr[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange);
    calcHist(&bgr[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange);
    calcHist(&bgr[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange);

    //绘制直方图
    int hist_w = 512, hist_h = 400;
    int bin_w = cvRound((double)hist_w / histSize);

    Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(255, 255, 255));
    //将结果归一化[0,histImage.rows]
    normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
    normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
    normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

    for (int i = 0; i < histSize; i++) {
        line(histImage, Point(bin_w * (i), hist_h),
            Point(bin_w * (i), hist_h - cvRound(b_hist.at<float>(i))), Scalar(255, 0, 0));
        line(histImage, Point(bin_w * (i), hist_h),
            Point(bin_w * (i), hist_h - cvRound(g_hist.at<float>(i))), Scalar(0, 255, 0));
        line(histImage, Point(bin_w * (i), hist_h ),
            Point(bin_w * (i), hist_h - cvRound(r_hist.at<float>(i))), Scalar(0, 0, 255));
    }
    return histImage;
}

int main(int argc, char** argv)
{
#if 0
	Mat src;
	src = imread("low_contrast.png");
	src.convertTo(src, CV_8U);
	std::cout << src.channels() << std::endl;
	imshow("origin", src);

	Mat histImage = histogramCal(src);
	imshow("hist", histImage);

	Mat hist;
	std::vector<Mat> bgr(3);
	split(src, bgr);
	equalizeHist(bgr[0], bgr[0]);
	equalizeHist(bgr[1], bgr[1]);
	equalizeHist(bgr[2], bgr[2]);

	Mat dst;
	merge(bgr, dst);
	imshow("equalize", dst);

	Mat equalHist = histogramCal(dst);
	imshow("equalHist", equalHist);
	waitKey();
#endif



    Mat src = imread("low_contrast.png", IMREAD_GRAYSCALE);
    
    Histogram1D hist1D;
    Mat histSrc = hist1D.getHistogramImge(src);
    imshow("src", src);
    imshow("histSrc", histSrc);
    Mat dst;
    hist1D.histogram_equalize(src, dst);
    Mat histDst = hist1D.getHistogramImge(dst);

    imshow("dst", dst);
    imshow("histDst", histDst);
    Mat dst2;
    equalizeHist(src, dst2);
    Mat histDst2 = hist1D.getHistogramImge(dst2);
    imshow("dst2", dst2);
    imshow("histDst2", histDst2);
    waitKey();

    return 0;
}




#endif