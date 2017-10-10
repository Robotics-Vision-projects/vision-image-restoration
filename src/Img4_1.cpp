
#include "Img4_1.h"

using namespace cv;

Img4_1::Img4_1(cv::Mat &src)
{
    this->source = src;
}

cv::Mat Img4_1::createNotchFilter()
{
    Mat img = source;
    Mat mag;
    int opt_rows = cv::getOptimalDFTSize(img.rows);
    int opt_cols = cv::getOptimalDFTSize(img.cols);
    copyMakeBorder(img, mag, 0, opt_rows - img.rows, 0, opt_cols - img.cols, BORDER_CONSTANT);

    mag.convertTo(mag, CV_32FC1);
    mag.setTo(1.f);
    cv::rectangle(mag, cv::Point(0.5*mag.cols/10.f, 0.5*mag.rows/10.f), cv::Point(9.5*mag.cols/10.f, 9.5*mag.rows/10.f), cv::Scalar(0), -1);


    Mat phase = Mat::zeros(mag.rows, mag.cols, CV_32FC1);

    Mat planes[] = {cv::Mat_<float>(mag), cv::Mat_<float>::zeros(mag.size())};
    //polarToCart(mag, phase, planes[0], planes[1]);
    //planes[0].convertTo(planes[0], CV_8UC1, 255);
    //imwrite("planes0.png", planes[0]);
    //imshow("real", planes[0]);
    Mat complex;
    merge(planes, 2, complex);
    mag.convertTo(mag, CV_8UC1, 255);
    imwrite("mag.png", mag);




    return complex;
}
