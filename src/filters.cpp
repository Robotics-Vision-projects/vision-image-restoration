
#include <filters.h>
#include <iostream>

using namespace std;


cv::Mat Filters::max_filter(cv::Mat &image, int max_rad)
{
    /* 
     * Substitute each pixel in the image by its local maxima
    */
    cv::Mat filtered_img;
    image.copyTo(filtered_img);
    // Create a new matrix with N extra cols and rows, filled with zeros.
    // (Zeros don't have any effect in the max filter).
    cv::Mat padded(image.rows+max_rad, image.cols+max_rad, CV_8UC1);
    cv::copyMakeBorder(image, padded, max_rad, max_rad, max_rad, max_rad,
                        cv::BORDER_CONSTANT, cv::Scalar::all(0));
    // Go through every pixel and apply the non-linear algorithm.
    for (auto row=max_rad; row<(padded.rows-max_rad); ++row){
        for (auto col=max_rad; col<(padded.cols-max_rad); ++col){
            // Select the maximum value inside the kernel window.
            // the radius will be incremented until a value higher than 0 is
            // found, or the maximum allowed radius is used.
            uchar max_value = 0;
            for (auto radius=1; radius<=max_rad; ++radius){
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
                // Look for the maximum value in the selected window.
                for (auto index=0; index<window.size(); ++index){
                    if (window[index] > max_value){
                        max_value = window[index];
                    }
                }
                if (max_value > 0){
                    break;
                }
            }
            filtered_img.at<uchar>(row-max_rad, col-max_rad) = max_value;
        }
    }
    return filtered_img;
}

cv::Mat Filters::adaptive_median_filter(cv::Mat &image, int max_rad)
{
    /* 
     * Substitute each pixel in the image by its local maxima
    */
    cv::Mat filtered_img;
    image.copyTo(filtered_img);
    // Create a new matrix with N extra cols and rows, filled with zeros.
    // (Zeros don't have any effect in the max filter).
    cv::Mat padded(image.rows+max_rad, image.cols+max_rad, CV_8UC1);
    cv::copyMakeBorder(image, padded, max_rad, max_rad, max_rad, max_rad,
                        cv::BORDER_CONSTANT, cv::Scalar::all(0));
    // Go through every pixel and apply the non-linear algorithm.
    for (auto row=max_rad; row<(padded.rows-max_rad); ++row){
        for (auto col=max_rad; col<(padded.cols-max_rad); ++col){
            // If the current pixel is not 0 or 255, let it unmodified.
            int center_pixel = padded.at<uchar>(row, col);
            if  (center_pixel != 0 && center_pixel != 255){
                filtered_img.at<uchar>(row-max_rad, col-max_rad) = center_pixel;
                continue;
            }
            // Select the maximum value inside the kernel window.
            // the radius will be incremented until a value higher than 0 is
            // found, or the maximum allowed radius is used.
            uchar median = 0;
            for (auto radius=1; radius<=max_rad; ++radius){
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
            filtered_img.at<uchar>(row-max_rad, col-max_rad) = median;
        }
    }
    return filtered_img;
}

cv::Mat Filters::intensity_enhancement(cv::Mat &gray_img, int increment){
    /* Increase the intensity of every pixel the specified value.
     *
     * The image is clipped, in order to keep pixel type coherency.
    */
    // Create the returned variable, and initialize to a copy of the input image
    cv::Mat enhanced_img;
    gray_img.copyTo(enhanced_img);
    // Loop through all pixels and add specified increment to their intensities.
    for (auto row=0; row<enhanced_img.rows; ++row){
        for (auto col=0; col<enhanced_img.cols; ++col){
            // saturate_cast function clips values exceeding variable limits.
            enhanced_img.at<uchar>(row, col) =  cv::saturate_cast<uchar>(
                    enhanced_img.at<uchar>(row, col) + increment); 
        }        
    }
    return enhanced_img;
}
