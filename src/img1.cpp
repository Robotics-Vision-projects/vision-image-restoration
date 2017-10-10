
// #include "Img1.h"
#include <filters.h>
#include <tools.h>

using namespace std;

int main(int argc, char** argv)
{
	// Read the first proposed image and get its histogram.
    cv::Mat image = cv::imread("./resources/Image1.png", cv::IMREAD_GRAYSCALE);
    cv::Mat hist_img = Tools::get_histogram(image);
    // Perform a max filter on the image and calculate its histogram.
    cv::Mat filtered_img = Filters::max_filter(image, 1);
    cv::Mat hist_filtered = Tools::get_histogram(filtered_img);
    // Show and save the filtered image.
    cv::namedWindow("filtered image", cv::WINDOW_NORMAL);
    cv::imshow("filtered image", filtered_img);
    cv::waitKey(0);
    cv::imwrite("./results/image1/max_filter_k1.png", filtered_img);
    // Show and save the histogram of the original image.
    cv::imshow("window", hist_img);
    cv::waitKey(0);
    cv::imwrite("./results/image1/original_histrogram.png", hist_img);
    // Show and save the histogram of the original image.
    cv::imshow("filtered histogram", hist_filtered);
    cv::waitKey(0);
    cv::imwrite("./results/image1/filtered_histrogram_k1.png", hist_filtered);
    return 0;
}