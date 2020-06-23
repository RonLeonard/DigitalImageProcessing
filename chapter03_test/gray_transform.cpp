//#define GRAY_TRANSFORM

#ifdef GRAY_TRANSFORM


#include <iostream>
#include <opencv.hpp>

using namespace cv;

int main()
{
/*image reverse*/
#if 0
    Mat img = imread("2.bmp", 0);
    Mat imgDst = ~img;
    imshow("Src Image", img);
    imshow("Src Image", imgDst);
    waitKey();
#endif
/*image log transform*/
#if 0
    Mat img = imread("2.jpg");
   c
    for (int i = 0; i < img.rows; i++)
    {
        for (int j = 0; j < img.cols; j++)
        {
            imgLog.at<Vec3f>(i, j)[0] = (log(1 + img.at<Vec3b>(i, j)[0]));
            imgLog.at<Vec3f>(i, j)[1] = (log(1 + img.at<Vec3b>(i, j)[1]));
            imgLog.at<Vec3f>(i, j)[2] = (log(1 + img.at<Vec3b>(i, j)[2]));
        }
    }
    normalize(imgLog, imgLog, 0, 255, CV_MINMAX);
    convertScaleAbs(imgLog, imgLog);
    imshow("src", img);
    imshow("dst", imgLog);
    waitKey();
#endif
/*image gamma transform*/
#if 0
    Mat img = imread("2.bmp");
    Mat img_gamma(img.size(), CV_32FC3);
    for (int i = 0; i < img.rows; i++)
    {
        for (int j = 0; j < img.cols; j++)
        {
            img_gamma.at<Vec3f>(i, j)[0] = pow(img.at<Vec3b>(i, j)[0], 0.7);
            img_gamma.at<Vec3f>(i, j)[1] = pow(img.at<Vec3b>(i, j)[1], 0.7);;
            img_gamma.at<Vec3f>(i, j)[2] = pow(img.at<Vec3b>(i, j)[2], 0.7);;
        }
    }
    normalize(img_gamma, img_gamma, 0, 255, CV_MINMAX);
    convertScaleAbs(img_gamma, img_gamma);
    imshow("src", img);
    imshow("dst", img_gamma);
    waitKey();
#endif
/*gray scale*/
#if 0
    Mat img = imread("low_contrast.png");
    if (img.empty())
    {
        printf("imread faild.\n");
        return -1;
    }
    Mat dst(img.size(), CV_32FC3);
    normalize(img, dst, 0, 255, CV_MINMAX);
    imshow("src", img);
    imshow("dst", dst);
    waitKey();
#endif

/*bit plane slicing*/
    Mat img = imread("4.jpg", 0);
    if (img.empty())
    {
        printf("imread faild.\n");
        return -1;
    }
    Mat img_bit1(img.size(), CV_8UC1);
    Mat img_bit2(img.size(), CV_8UC1);
    Mat img_bit3(img.size(), CV_8UC1);
    Mat img_bit4(img.size(), CV_8UC1);
    Mat img_bit5(img.size(), CV_8UC1);
    Mat img_bit6(img.size(), CV_8UC1);
    Mat img_bit7(img.size(), CV_8UC1);
    Mat img_bit8(img.size(), CV_8UC1);
    for (int i = 0; i < img.rows; i++)
    {
        for (int j = 0; j < img.cols; j++)
        {
            img_bit8.at<uchar>(i, j) = img.at<uchar>(i, j) & 128;
            img_bit7.at<uchar>(i, j) = img.at<uchar>(i, j) & 64;
            img_bit6.at<uchar>(i, j) = img.at<uchar>(i, j) & 32;
            img_bit5.at<uchar>(i, j) = img.at<uchar>(i, j) & 16;
            img_bit4.at<uchar>(i, j) = img.at<uchar>(i, j) & 8;
            img_bit3.at<uchar>(i, j) = img.at<uchar>(i, j) & 4;
            img_bit2.at<uchar>(i, j) = img.at<uchar>(i, j) & 2;
            img_bit1.at<uchar>(i, j) = img.at<uchar>(i, j) & 1;
        }
    }
       

    imshow("src", img);
    imshow("img_bit1", img_bit1);
    imshow("img_bit2", img_bit2);
    imshow("img_bit3", img_bit3);
    imshow("img_bit4", img_bit4);
    imshow("img_bit5", img_bit5);
    imshow("img_bit6", img_bit6);
    imshow("img_bit7", img_bit7);
    imshow("img_bit8", img_bit8);
    waitKey();
    return 0;
}

#endif