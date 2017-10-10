
#include <filters.h>
#include <tools.h>

using namespace std;


int main(int argc, char** argv)
{
	// Read the first proposed image and get its histogram.
    cv::Mat image = cv::imread("./resources/Image1.png", cv::IMREAD_GRAYSCALE);
    cv::Mat hist_img = Tools::get_histogram(image);
    // Perform a max filter on the image and calculate its histogram.
    cv::Mat filtered_img = Filters::max_filter(image, 5);
    cv::Mat hist_filtered = Tools::get_histogram(filtered_img);
    // Apply standard median filter.
    cv::Mat median_img; 
    cv::medianBlur(filtered_img, median_img, 3);
    cv::Mat hist_median = Tools::get_histogram(median_img);
    // Enhance intensity values.
    cv::Mat enhanced_img = Filters::intensity_enhancement(median_img, 50);
    cv::Mat hist_enhanced = Tools::get_histogram(enhanced_img);
    // Show and save the filtered image.
    cv::namedWindow("filtered image", cv::WINDOW_NORMAL);
    cv::imshow("filtered image", filtered_img);
    cv::waitKey(0);
    cv::imwrite("./results/image1/01-max_filter_k3.png", filtered_img);
    // Show and save the image filtered with the median filter.
    cv::namedWindow("median image", cv::WINDOW_NORMAL);
    cv::imshow("median image", median_img);
    cv::waitKey(0);
    cv::imwrite("./results/image1/02-median_filter.png", median_img);
    // Show and save the intensity enhanced.
    cv::namedWindow("enhanced image", cv::WINDOW_NORMAL);
    cv::imshow("enhanced image", enhanced_img);
    cv::waitKey(0);
    cv::imwrite("./results/image1/03-enhanced.png", enhanced_img);
    // Show and save the histogram of the original image.
    cv::imshow("original histogram", hist_img);
    cv::waitKey(0);
    cv::imwrite("./results/image1/00-original_histrogram.png", hist_img);
    // Show and save the histogram of the filtered image.
    cv::imshow("filtered histogram", hist_filtered);
    cv::waitKey(0);
    cv::imwrite("./results/image1/01-filtered_histrogram_k3.png", hist_filtered);
    // Show and save the histogram of the original image.
    cv::imshow("median histogram", hist_median);
    cv::waitKey(0);
    cv::imwrite("./results/image1/02-median_histrogram.png", hist_img);
    // Show and save the histogram of the original image.
    cv::imshow("intensity enhanced histogram", hist_enhanced);
    cv::waitKey(0);
    cv::imwrite("./results/image1/03-enhanced_histrogram.png", hist_img);
    return 0;
}