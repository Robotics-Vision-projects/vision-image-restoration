
#include <tools.h>

int main(int argc, char** agrv)
{
    cv::Mat test = cv::imread("Image4_1.png", cv::IMREAD_GRAYSCALE);
    Tools::spectrumDebug(test);
    return 0;
}
