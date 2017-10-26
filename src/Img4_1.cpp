
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

    //expand borders to fit source
    int opt_rows = cv::getOptimalDFTSize(mag.rows);
    int opt_cols = cv::getOptimalDFTSize(mag.cols);
    //cv::Mat mag2 = mag.clone();
    copyMakeBorder(mag, mag, 0, opt_rows - mag.rows, 0, opt_cols - mag.cols, BORDER_CONSTANT);

    //cv::rectangle(mag, cv::Point(2.7*mag.cols/10.f, 2.7*mag.rows/10.f), cv::Point(7.3*mag.cols/10.f, 7.3*mag.rows/10.f), cv::Scalar(0), -1);
    // FILTER FUNCTION
    int x1, x2, x3, x4, y1, y2, y3, y4;
    int n = 6;
    int n2 = 2;
    int D0 = 50;
    int D1 = 40;
    x1 = 1070;//1064;
    y1 = 889;//931;
    x2 = mag.cols - x1;
    y2 = mag.rows - y1;
    x3 = 668;
    y3 = 1097;
    x4 = mag.cols - x3;
    y4 = mag.rows - y3;

    // 1070, 889
    // 668, 1097
    for(size_t i = 0; i < mag.rows; ++i)
    {
        for(size_t j = 0; j < mag.cols; ++j)
        {
            if( j > mag.cols/2)     // right side
            {
                if(i < mag.rows/2)  // top
                {
                    mag.at<float>(i, j) = 1/(1 + std::pow(std::sqrt( (i-y1)*(i-y1) + (j-x1)*(j-x1) )/ D0, -2*n));
                }
                else                // bottom
                {
                    mag.at<float>(i, j) = 1/(1 + std::pow(std::sqrt( (i-y4)*(i-y4) + (j-x4)*(j-x4) )/ D1, -2*n2));
                }
            }
            else                    // left side
            {
                if(i > mag.rows/2)  // bottom
                {
                    mag.at<float>(i, j) = 1/(1 + std::pow(std::sqrt( (i-y2)*(i-y2) + (j-x2)*(j-x2) )/ D0, -2*n));
                }
                else                // top
                {
                    mag.at<float>(i, j) = 1/(1 + std::pow(std::sqrt( (i-y3)*(i-y3) + (j-x3)*(j-x3) )/ D1, -2*n2));
                }
            }

        }
    }

    //---------------------------------


    Tools::dftshift(mag);

    Mat phase = Mat::zeros(mag.rows, mag.cols, CV_32FC1);
    Mat planes[] = {cv::Mat_<float>::zeros(mag.size()), cv::Mat_<float>::zeros(mag.size())};
    polarToCart(mag, phase, planes[0], planes[1]);

    Mat complex;
    merge(planes, 2, complex);

    //mag.convertTo(mag, CV_8UC1, 255);
    //imwrite("filterMagnitude.png", mag);

    return complex;
}
