
#include <tools.h>

#include <Img3.h>
#include <Img4_1.h>

int main(int argc, char** agrv)
{

    // Image 4 ---------------------------------------------------------
    /*cv::Mat img4_1 = cv::imread("Image4_1.png", cv::IMREAD_GRAYSCALE);
    Img4_1 img4(img4_1);
    cv::Mat filter = img4.createNotchFilter();

    Tools::applyFreqFilter(img4.source, img4.result, filter);

    img4.result.convertTo(img4.result, CV_8UC1, 255);
    imwrite("result.png", img4.result);*/

    // Image 3 --------------------------------------------------------

    cv::Mat img3_ = cv::imread("Image3.png", cv::IMREAD_GRAYSCALE);
    Img3 img3(img3_);
    img3.adaptiveNoiseReduction(3, 5);


    // other approaches ------------------------------------------

    //cv::medianBlur(img3.source, img3.result, 7);

    //cv::GaussianBlur(img3.source, img3.result, cv::Size(7, 7), 0);

    // this algorithm works wey well, but is not very educational :)
    //cv::fastNlMeansDenoising(img3.source, img3.result, 10);

    //-------------------------------------------------------------

    cv::imwrite("3result.png", img3.result);
    return 0;
}


/*
char dat[9] = {2,2,2,2,2,2,2,2,2};
cv::Mat tst(3, 3, CV_8UC1, dat);
std::cout << std::endl;
cv::Scalar dev, mean;
cv::meanStdDev(tst, mean, dev);
std::cout << dev[0] << std::endl << mean[0];
*/
