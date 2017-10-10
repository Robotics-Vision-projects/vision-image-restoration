
#include <filters.h>
#include <iostream>

using namespace std;


// Substitute each pixel by the local maxima
cv::Mat Filters::max_filter(cv::Mat &image)
{
    cv::Mat filtered_img;
    image.copyTo(filtered_img);
    // Create a new matrix with 2 extra cols and rows, filled with zeros.
    // (Zeros don't have any effect in the max filter).
    cv::Mat padded(image.rows+2, image.cols+2, CV_8UC1);
    cv::copyMakeBorder(image, padded, 1, 1, 1, 1, cv::BORDER_CONSTANT,
                       cv::Scalar::all(0));
    // Go through every pixel and apply the non-linear algorithm.
    vector <int> window(9);
    for (auto row=1; row<(padded.rows-1); ++row){
        for (auto col=1; col<(padded.cols-1); ++col){
            window[0] = padded.at<uchar>(row-1, col-1);
            window[1] = padded.at<uchar>(row-1, col);
            window[2] = padded.at<uchar>(row-1, col+1);
            window[3] = padded.at<uchar>(row, col-1);
            window[4] = padded.at<uchar>(row, col);
            window[5] = padded.at<uchar>(row, col+1);
            window[6] = padded.at<uchar>(row+1, col-1);
            window[7] = padded.at<uchar>(row+1, col);
            window[8] = padded.at<uchar>(row+1, col+1);
            // Select the maximum value inside the 3x3 window.
            int max_value = 0;
            for (int index=0; index<9; ++index)
                if (window[index] > max_value){
                    max_value = window[index];
                }
            filtered_img.at<uchar>(row-1, col-1) = max_value;
        }
    }
    cout << "original rowsxcols: " << image.rows << "x" << image.cols << "\n";
    cout << "padded rowsxcols: " << padded.rows << "x" << padded.cols << "\n";
    return filtered_img;
}