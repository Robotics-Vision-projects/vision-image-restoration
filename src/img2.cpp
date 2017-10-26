
#include <filters.h>
#include <tools.h>

using namespace std;


int main(int argc, char** argv)
{
    // Compression parameters
    vector<int> comp;
    comp.push_back(CV_IMWRITE_JPEG_QUALITY);
    // 40 for compressed images, 100 por uncompressed.
    comp.push_back(40);
	// Read the first proposed image.
    cv::Mat image = cv::imread("./resources/Image2.png", cv::IMREAD_GRAYSCALE);
    cv::namedWindow("original image", cv::WINDOW_NORMAL);
    cv::imshow("original image", image);
    // Perform an adaptive median filter.
    cv::Mat filtered_img_1 = Filters::adaptive_median_filter(image, 1);
    cv::Mat filtered_img_2 = Filters::adaptive_median_filter(image, 2);
    cv::Mat filtered_img = Filters::adaptive_median_filter(image, 3);
    cv::Mat filtered_img_4 = Filters::adaptive_median_filter(image, 4);
    cv::namedWindow("filtered image", cv::WINDOW_NORMAL);
    cv::imwrite("./results/image2/01-med_filter_k1.jpg", filtered_img_1, comp);
    cv::imwrite("./results/image2/01-med_filter_k2.jpg", filtered_img_2, comp);
    cv::imwrite("./results/image2/01-med_filter_k3.jpg", filtered_img, comp);
    cv::imwrite("./results/image2/01-med_filter_k4.jpg", filtered_img_4, comp);
    cv::imshow("filtered image", filtered_img);
    // Perform an adaptive max filter and calculate its histogram.
    cv::Mat max_filtered_img = Filters::max_filter(filtered_img, 2);
    cv::namedWindow("max filtered image", cv::WINDOW_NORMAL);
    cv::imshow("max filtered image", max_filtered_img);
    cv::imwrite("./results/image2/02-max_filter_k2.jpg", max_filtered_img,
                comp);
    // Enhance intensity values with the log transform.
    cv::Mat log_enhanced_img = Tools::log_transform(max_filtered_img);
    cv::namedWindow("enhanced image", cv::WINDOW_NORMAL);
    cv::imshow("enhanced image", log_enhanced_img);
    cv::imwrite("./results/image2/03-log_transformed.jpg", log_enhanced_img,
                comp);
    // Enhance intensity values with the gamma correction.
    cv::Mat gamma_corr_img = Tools::gamma_correction(max_filtered_img, 0.6);
    cv::Mat gamma_corr_img_04 = Tools::gamma_correction(max_filtered_img, 0.4);
    cv::Mat gamma_corr_img_02 = Tools::gamma_correction(max_filtered_img, 0.2);
    cv::Mat gamma_corr_img_01 = Tools::gamma_correction(max_filtered_img, 0.1);
    cv::namedWindow("gamma enhanced image", cv::WINDOW_NORMAL);
    cv::imwrite("./results/image2/03-gamma_transformed_06.jpg",
                gamma_corr_img, comp);
    cv::imwrite("./results/image2/03-gamma_transformed_04.jpg",
                gamma_corr_img_04, comp);
    cv::imwrite("./results/image2/03-gamma_transformed_02.jpg",
                gamma_corr_img_02, comp);
    cv::imwrite("./results/image2/03-gamma_transformed_01.jpg",
                gamma_corr_img_01, comp);
    cv::imshow("gamma enhanced image", gamma_corr_img);
    // Apply a gaussian filter to the image
    cv::Mat gauss_filtered_img;
    cv::GaussianBlur(gamma_corr_img, gauss_filtered_img, cv::Size(3,3), 3);
    cv::Mat gauss_filtered_img_5;
    cv::GaussianBlur(gamma_corr_img, gauss_filtered_img_5, cv::Size(5,5), 3);
    cv::Mat gauss_filtered_img_7;
    cv::GaussianBlur(gamma_corr_img, gauss_filtered_img_7, cv::Size(7,7), 3);
    cv::namedWindow("Gauss smoothed image", cv::WINDOW_NORMAL);
    cv::imwrite("./results/image2/04-gauss_k3.jpg", gauss_filtered_img, comp);
    cv::imwrite("./results/image2/04-gauss_k5.jpg", gauss_filtered_img_5, comp);
    cv::imwrite("./results/image2/04-gauss_k7.jpg", gauss_filtered_img_7, comp);
    cv::imshow("Gauss smoothed image", gauss_filtered_img);
    // Apply a mean filter to the image
    cv::Mat mean_filtered_img;
    cv::blur(gamma_corr_img, mean_filtered_img, cv::Size(3,3));
    cv::Mat mean_filtered_img_5;
    cv::blur(gamma_corr_img, mean_filtered_img_5, cv::Size(5,5));
    cv::namedWindow("Gauss smoothed image", cv::WINDOW_NORMAL);
    cv::imwrite("./results/image2/04-mean_k3.jpg", mean_filtered_img, comp);
    cv::imwrite("./results/image2/04-mean_k5.jpg", mean_filtered_img_5, comp);
    cv::imshow("Mean filtered image", mean_filtered_img);
    cv::waitKey(0);
	return 0;
}
