
// #include "Img1.h"
#include <tools.h>

int main(int argc, char** argv)
{
    cv::Mat image = cv::imread("./resources/Image1.png", cv::IMREAD_GRAYSCALE);
    Tools::spectrumDebug(image);
    return 0;
}