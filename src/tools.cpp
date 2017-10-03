
#include <tools.h>

// Rearranges the quadrants of a Fourier image so that the origin is at the center of the image.
void Tools::dftshift(cv::Mat& mag)
{
    int cx = mag.cols / 2;
    int cy = mag.rows / 2;

    cv::Mat tmp;
    cv::Mat q0(mag, cv::Rect(0, 0, cx, cy));
    cv::Mat q1(mag, cv::Rect(cx, 0, cx, cy));
    cv::Mat q2(mag, cv::Rect(0, cy, cx, cy));
    cv::Mat q3(mag, cv::Rect(cx, cy, cx, cy));

    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);

    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);
}

bool Tools::spectrumDebug(cv::Mat &input)
{
    cv::Mat img = input.clone();
    if(img.channels() != 1)
    {
        std::cout << std::endl << "Error: this function is for single channel grayscale images, channels: " << img.channels();
        return false;
    }

    // Expand the image to an optimal size.
    cv::Mat padded;
    int opt_rows = cv::getOptimalDFTSize(img.rows);
    int opt_cols = cv::getOptimalDFTSize(img.cols);
    cv::copyMakeBorder(img, padded, 0, opt_rows - img.rows, 0, opt_cols - img.cols, cv::BORDER_CONSTANT);

    // Make place for both the real and complex values by merging planes into a
    // cv::Mat with 2 channels.
    // Use float element type because frequency domain ranges are large.
    cv::Mat planes[] = {cv::Mat_<float>(padded), cv::Mat_<float>::zeros(padded.size())};
    cv::Mat complex;
    cv::merge(planes, 2, complex);

    // Compute DFT
    cv::dft(complex, complex);

    // Split real and complex planes (you can reuse the 'planes' array to save the result)
    cv::split(complex, planes);

    // Compute the magnitude and phase (see e.g. cv::cartToPolar)
    cv::Mat mag, phase;
    cv::cartToPolar(planes[0], planes[1], mag, phase);

    // Shift quadrants so the Fourier image origin is in the center of the image
    // (see above dtfshift function)
    dftshift(mag);

    // Switch to logarithmic scale to be able to display on screen
    mag += cv::Scalar::all(1);
    cv::log(mag, mag);

    // Transform the matrix with float values into a viewable image form (float
    // values between 0 and 1) and show the result.
    cv::normalize(mag, mag, 0, 1, cv::NORM_MINMAX);
    cv::normalize(phase, phase, 0, 1, cv::NORM_MINMAX);
    mag.convertTo(mag, CV_8UC1, 255);
    cv::imwrite("debug/magnitude.png", mag);
    phase.convertTo(phase, CV_8UC1, 255);
    cv::imwrite("debug/phase.png", phase);

    return true;

}

bool Tools::applyFreqFilter(cv::Mat &input, cv::Mat &output, cv::Mat &filter)
{
    cv::Mat img = input.clone();
    if(img.channels() != 1)
    {
        std::cout << std::endl << "Error: this function is for single channel grayscale images, channels: " << img.channels();
        return false;
    }

    // Expand the image to an optimal size.
    cv::Mat padded;
    int opt_rows = cv::getOptimalDFTSize(img.rows);
    int opt_cols = cv::getOptimalDFTSize(img.cols);
    cv::copyMakeBorder(img, padded, 0, opt_rows - img.rows, 0, opt_cols - img.cols, cv::BORDER_CONSTANT);

    // Make place for both the real and complex values by merging planes into a
    // cv::Mat with 2 channels.
    // Use float element type because frequency domain ranges are large.
    cv::Mat planes[] = {cv::Mat_<float>(padded), cv::Mat_<float>::zeros(padded.size())};
    cv::Mat complex;
    cv::merge(planes, 2, complex);

    // Compute DFT
    cv::dft(complex, complex);

    //apply frequency domain filter
    cv::mulSpectrums(complex, filter, complex, 0);

    cv::Mat filtered; // the resulting filtered image
    cv::dft(complex, complex, cv::DFT_INVERSE + cv::DFT_SCALE);
    cv::split(complex, planes);
    cv::magnitude(planes[0], planes[1], filtered);

    // Normalize and show filtered image
    cv::normalize(filtered, filtered, 0, 1, cv::NORM_MINMAX);
    output = filtered.clone();
    return true;

}
