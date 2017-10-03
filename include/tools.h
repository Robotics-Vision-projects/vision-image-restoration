#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>

class Tools
{

public:

    /// \brief Rearranges the quadrants of a Fourier image so that the origin is at the center of the image
    static void dftshift(cv::Mat& mag);

    /// \brief creates and stores the frequency domain images from the input image
    /// \param input this is the input image
    /// \return true = success, false = error
    ///
    /// this would be the detailed description
    static bool spectrumDebug(cv::Mat& input);

    /// \brief apllies a frequency domain filter (with mulSpectrums() ) to the input image, and returns the filtered image
    /// \param input input image
    /// \param output output image is return here
    /// \param filter complex channel filter matrix
    ///
    /// UNFINISHED
    static bool applyFreqFilter(cv::Mat& input, cv::Mat& output, cv::Mat& filter);

};
