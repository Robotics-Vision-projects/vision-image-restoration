
#include "Img4_1.h"
#include "tools.h"

using namespace cv;

Img4_1::Img4_1(cv::Mat &src)
{
    this->source = src;
}

cv::Mat Img4_1::createNotchFilter()
{
    Mat img = source;
    Mat mag(img.rows, img.cols, CV_32FC1);
    mag.setTo(1.f);

    //Tools::dftshift(mag);

    //cv::rectangle(mag, cv::Point(4.7*mag.cols/10.f, 4.7*mag.rows/10.f), cv::Point(5.3*mag.cols/10.f, 5.3*mag.rows/10.f), cv::Scalar(0), -1);
    // FILTER FUNCTION
    int x1, x2,y1, y2;
    int n = 3;
    int D0 = 100;
    x1 = mag.cols/2 + 200;
    y1 = mag.rows/2 + 200;
    x2 = mag.cols - x1;
    y2 = mag.rows - y1;

    for(size_t i = 0; i < mag.rows; ++i)
    {
        for(size_t j = 0; j < mag.cols; ++j)
        {
            if( j > mag.cols/2)     // right side
            {
                mag.at<float>(i, j) = 1/(1 + std::pow(std::sqrt( (i-y1)*(i-y1) + (j-x1)*(j-x1) )/ D0, -2*n));
            }
            else                    // left side
            {
                mag.at<float>(i, j) = 1/(1 + std::pow(std::sqrt( (i-y2)*(i-y2) + (j-x2)*(j-x2) )/ D0, -2*n));
            }

        }
    }

    mag.convertTo(mag, CV_8UC1, 255);
    imwrite("mag2.png", mag);
    mag.convertTo(mag, CV_32FC1, 1/255.f);

    //---------------------------------


    Tools::dftshift(mag);

    //expand borders to fit source
    int opt_rows = cv::getOptimalDFTSize(img.rows);
    int opt_cols = cv::getOptimalDFTSize(img.cols);
    copyMakeBorder(mag, mag, 0, opt_rows - img.rows, 0, opt_cols - img.cols, BORDER_CONSTANT);

    Mat phase = Mat::zeros(mag.rows, mag.cols, CV_32FC1);

    Mat planes[] = {cv::Mat_<float>(mag), cv::Mat_<float>::zeros(mag.size())};
    polarToCart(mag, phase, planes[0], planes[1]);

    Mat complex;
    merge(planes, 2, complex);

    //planes[0].convertTo(planes[0], CV_8UC1, 255);
    //imwrite("planes0.png", planes[0]);
    //imshow("real", planes[0]);

    mag.convertTo(mag, CV_8UC1, 255);
    imwrite("mag.png", mag);

    return complex;
}
