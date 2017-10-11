
#include <filters.h>
#include <tools.h>

using namespace std;


int main(int argc, char** argv)
{
	// Read the first proposed image and get its histogram.
    cv::Mat image = cv::imread("./resources/Image2.png", cv::IMREAD_GRAYSCALE);
    cv::Mat hist_img = Tools::get_histogram(image);

    // Show and save the histogram of the original image.
    cv::imshow("original histogram", hist_img);
    cv::waitKey(0);
    cv::imwrite("./results/image2/00-original_histrogram.png", hist_img);
    return 0;
}
