
#include <filters.h>
#include <tools.h>

using namespace std;


int main(int argc, char** argv)
{
	// Read the first proposed image and get its histogram.
    cv::Mat image = cv::imread("./resources/Image2.png", cv::IMREAD_GRAYSCALE);
    cv::Mat hist_img = Tools::get_histogram(image);
    // Perform an adaptive median filter and calculate its histogram.
    cv::Mat filtered_img = Filters::adaptive_median_filter(image, 4);
    cv::Mat hist_filtered = Tools::get_histogram(filtered_img);
    // Enhance intensity values.
    cv::Mat enhanced_img = Tools::log_transform(filtered_img);
    cv::Mat hist_enhanced = Tools::get_histogram(enhanced_img);
    // Show and save the histogram of the original image.
    cv::imshow("original histogram", hist_img);
    cv::waitKey(0);
    cv::imwrite("./results/image2/00-original_histrogram.png", hist_img);
    // Show and save the filtered image.
    cv::namedWindow("filtered image", cv::WINDOW_NORMAL);
    cv::imshow("filtered image", filtered_img);
    cv::waitKey(0);
    cv::imwrite("./results/image2/01-med_filter_k4.png", filtered_img);
    // Show and save the intensity enhanced.
    cv::namedWindow("enhanced image", cv::WINDOW_NORMAL);
    cv::imshow("enhanced image", enhanced_img);
    cv::waitKey(0);
    cv::imwrite("./results/image2/02-log_transormed.png", enhanced_img);
	return 0;
}
