
#include <tools.h>

#include <Img4_1.h>

int main(int argc, char** agrv)
{
    cv::Mat img4_1 = cv::imread("Image4_1.png", cv::IMREAD_GRAYSCALE);
    Img4_1 img4(img4_1);
    cv::Mat filter = img4.createNotchFilter();
    //cv::Mat plans[] = {cv::Mat_<float>(padded), cv::Mat_<float>::zeros(padded.size())};
        //cv::split(filter, plans);
        //plans[0].convertTo(plans[0], CV_8UC1, 255);
        //imwrite("PLAN0.png", plans[0]);
    Tools::applyFreqFilter(img4.source, img4.result, filter);

    //Tools::spectrumDebug(img4.source);

    filter.convertTo(filter, CV_8UC1, 255);
    //imwrite("", filter);
    //img4.result.convertTo(img4.result, CV_8UC1, 255);
    imwrite("result.png", img4.result);
    //cv::imshow("test", img4.result);
    //cv::waitKey();
    return 0;
}
