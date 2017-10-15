
#include <filters.h>
#include <tools.h>

using namespace std;


int main(int argc, char** argv)
{
	// Read the first proposed image and get its histogram.
    cv::Mat image = cv::imread("./resources/Image2.png", cv::IMREAD_GRAYSCALE);
    cv::Mat hist_img = Tools::get_histogram(image);
    // Perform an adaptive median filter and calculate its histogram.
    cv::Mat filtered_img = Filters::adaptive_median_filter(image, 3);
    cv::Mat hist_filtered = Tools::get_histogram(filtered_img);
    // Perform an adaptive max filter and calculate its histogram.
    cv::Mat max_filtered_img = Filters::max_filter(filtered_img, 3);
    // Enhance intensity values with the log transform.
    cv::Mat log_enhanced_img = Tools::log_transform(max_filtered_img);
    cv::Mat hist_log_enhanced = Tools::get_histogram(log_enhanced_img);
    // Enhance intensity values with the gamma correction.
    cv::Mat gamma_enhanced_img = Tools::gamma_correction(max_filtered_img, 0.4);
    cv::Mat hist_gamma_enhanced = Tools::get_histogram(gamma_enhanced_img);
    // Apply a gaussian filter to the image
    cv::Mat gauss_filtered_img;
    cv::GaussianBlur(gamma_enhanced_img, gauss_filtered_img, cv::Size(3,3), 3);
    // Show the original image.
    cv::namedWindow("original image", cv::WINDOW_NORMAL);
    cv::imshow("original image", image);
    cv::waitKey(0);
    // Show and save the histogram of the original image.
    cv::imshow("original histogram", hist_img);
    cv::waitKey(0);
    cv::imwrite("./results/image2/00-original_histrogram.png", hist_img);
    // Show and save the filtered image.
    cv::namedWindow("filtered image", cv::WINDOW_NORMAL);
    cv::imshow("filtered image", filtered_img);
    cv::waitKey(0);
    cv::imwrite("./results/image2/01-med_filter_k3.png", filtered_img);
    // Show and save the max filtered image.
    cv::namedWindow("max filtered image", cv::WINDOW_NORMAL);
    cv::imshow("max filtered image", max_filtered_img);
    cv::waitKey(0);
    cv::imwrite("./results/image2/02-max_filter_k3.png", max_filtered_img);
    // Show and save the intensity log enhanced.
    cv::namedWindow("enhanced image", cv::WINDOW_NORMAL);
    cv::imshow("enhanced image", log_enhanced_img);
    cv::waitKey(0);
    cv::imwrite("./results/image2/03-log_transormed.png", log_enhanced_img);
    // Show and save the intensity gamma enhanced.
    cv::namedWindow("gamma enhanced image", cv::WINDOW_NORMAL);
    cv::imshow("gamma enhanced image", gamma_enhanced_img);
    cv::waitKey(0);
    cv::imwrite("./results/image2/03-gamma_transormed.png", gamma_enhanced_img);
    // Show and save the gaussian filtered image.
    cv::namedWindow("Gauss smoothed image", cv::WINDOW_NORMAL);
    cv::imshow("Gauss smoothed image", gauss_filtered_img);
    cv::waitKey(0);
    cv::imwrite("./results/image2/04-gauss_filtered.png", gauss_filtered_img);
	return 0;
}
