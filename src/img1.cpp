
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
    // Read the first proposed image and get its histogram.
    cv::Mat image = cv::imread("./resources/Image1.png", cv::IMREAD_GRAYSCALE);
    cv::Mat hist_img = Tools::get_histogram(image);
    cv::namedWindow("original image", cv::WINDOW_NORMAL);
    cv::imshow("original image", image);
    cv::imwrite("./results/image1/00-original_histrogram.png", hist_img);
    // Perform a max filter on the image and calculate its histogram.
    cv::Mat filtered_img_1 = Filters::max_filter(image, 1);
    cv::Mat filtered_img_2 = Filters::max_filter(image, 2);
    cv::Mat filtered_img_3 = Filters::max_filter(image, 3);
    cv::imwrite("./results/image1/01-max_filter_k1.jpg", filtered_img_1, comp);
    cv::imwrite("./results/image1/01-max_filter_k2.jpg", filtered_img_2, comp);
    cv::imwrite("./results/image1/01-max_filter_k3.jpg", filtered_img_3, comp);
    cv::namedWindow("filtered image", cv::WINDOW_NORMAL);
    cv::imshow("filtered image", filtered_img_3);
    // Apply standard median filter.
    cv::Mat median_img; 
    cv::medianBlur(filtered_img_3, median_img, 3);
    cv::namedWindow("median image", cv::WINDOW_NORMAL);
    cv::imshow("median image", median_img);
    cv::imwrite("./results/image1/02-median_filter.jpg", median_img, comp);
    // Enhance intensity values.
    cv::Mat enhanced_img = Filters::intensity_enhancement(median_img, 50);
    cv::Mat log_enhanced_img = Tools::log_transform(median_img);
    cv::imwrite("./results/image1/03-enhanced50.jpg", enhanced_img, comp);
    cv::imwrite("./results/image1/03-log_transormed.jpg", log_enhanced_img,
                comp);
    cv::namedWindow("enhanced image", cv::WINDOW_NORMAL);
    cv::imshow("enhanced image", log_enhanced_img);
    cv::waitKey(0);
    return 0;
}