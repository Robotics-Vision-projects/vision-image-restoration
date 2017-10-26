
#include "Img3.h"

using namespace std;

Img3::Img3(cv::Mat &src)
{
    this->source = src;
}

void Img3::adaptiveNoiseReduction(int lKernelRadius, int gKernelRadius)
{
    cv::Mat filtered_img;
    source.copyTo(filtered_img);
    cv::Mat padded(source.rows+gKernelRadius*2, source.cols+gKernelRadius*2, CV_8UC1);
    cv::copyMakeBorder(source, padded, gKernelRadius, gKernelRadius, gKernelRadius, gKernelRadius,
                       cv::BORDER_CONSTANT, cv::mean(source));


    // Go through every pixel and apply the algorithm. f = g - (var_global/var_local)*(g - mean_local)
    for (auto row=gKernelRadius; row<(padded.rows-gKernelRadius); ++row){
        for (auto col=gKernelRadius; col<(padded.cols-gKernelRadius); ++col){

            cv::Mat locKernel = padded(cv::Range(row - lKernelRadius, row + lKernelRadius),
                                         cv::Range(col-lKernelRadius, col + lKernelRadius));
            // globKernel needs its own allocated space because of the blurring
            cv::Mat globKernel = cv::Mat(padded(cv::Range(row - gKernelRadius, row + gKernelRadius),
                                        cv::Range(col-gKernelRadius, col + gKernelRadius))).clone();
            // apply a gaussian blur to gain the variance of the actual scene with less noise
            cv::GaussianBlur(globKernel, globKernel, cv::Size(3,3), 0);
            cv::Scalar locMean, globMean, locDev, globDev;
            cv::meanStdDev(locKernel, locMean, locDev);
            cv::meanStdDev(globKernel, globMean, globDev);

            // if the local variance is lower, do nothing
            // if local variance is 0, do nothing because we can't divide by 0
            if  (locDev[0] < globDev[0] || locDev[0] == 0)
            {
                filtered_img.at<uchar>(row-gKernelRadius, col-gKernelRadius) = padded.at<uchar>(row, col);
            }
            // otherwise calculate value of f(u,v)
            else
            {

                uchar g = padded.at<uchar>(row, col);
                float ratio = sqrt(globDev[0]/locDev[0]);

                uchar f = (int)(0.5 + g - ratio*(g - locMean[0]));
                filtered_img.at<uchar>(row-gKernelRadius, col-gKernelRadius) = f;
            }
        }
    }
    result = filtered_img.clone();
}

/*
for (auto radius=1; radius<=lKernelRadius; ++radius){
    cv::Mat roi_img = padded(cv::Range(row-radius, row+radius),
                             cv::Range(col-radius, col+radius));
    // Convert the ROI cv::Mat to a std::vector.
    vector<uchar> window(pow(2*radius+1, 2));
    for (auto krow = 0; krow < roi_img.rows; ++krow){
        for (auto kcol = 0; kcol < roi_img.cols; ++kcol){
            window[krow*roi_img.cols + kcol] =
                    roi_img.at<uchar>(krow, kcol);
        }
    }
    // Calculate the vector median value. Break the loop if it is
    // not an extreme value.
    int ksize = pow(radius*2 + 1, 2);
    sort(window.begin(), window.end());
    median = window[ksize/2];
    if (median != 0 && median != 255){
        break;
    }
}
*/
