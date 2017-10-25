
#include <tools.h>

#include <Img3.h>
#include <Img4_1.h>

int main(int argc, char** agrv)
{
    /*cv::Mat img4_1 = cv::imread("Image4_1.png", cv::IMREAD_GRAYSCALE);
    Img4_1 img4(img4_1);
    cv::Mat filter = img4.createNotchFilter();

    Tools::applyFreqFilter(img4.source, img4.result, filter);

    img4.result.convertTo(img4.result, CV_8UC1, 255);
    imwrite("result.png", img4.result);*/

    cv::Mat img3_ = cv::imread("Image3.png", cv::IMREAD_GRAYSCALE);
    Img3 img3(img3_);
    // this algorithm works wey well for Gaussian noise, but is not very educational :)
    cv::fastNlMeansDenoising(img3.source, img3.result, 10);

    cv::imwrite("3result.png", img3.result);
    return 0;
}
