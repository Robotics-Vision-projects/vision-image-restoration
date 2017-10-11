
#include <tools.h>

using namespace std;

// Rearranges the quadrants of a Fourier image so that the origin is at the
// center of the image.
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
        std::cout << std::endl << "Error: this function is for single channel "
                "grayscale images, channels: " << img.channels();
        return false;
    }

    // Expand the image to an optimal size.
    cv::Mat padded;
    int opt_rows = cv::getOptimalDFTSize(img.rows);
    int opt_cols = cv::getOptimalDFTSize(img.cols);
    cv::copyMakeBorder(img, padded, 0, opt_rows - img.rows, 0,
                       opt_cols - img.cols, cv::BORDER_CONSTANT);

    // Make place for both the real and complex values by merging planes into a
    // cv::Mat with 2 channels.
    // Use float element type because frequency domain ranges are large.
    cv::Mat planes[] = {cv::Mat_<float>(padded),
                        cv::Mat_<float>::zeros(padded.size())};
    cv::Mat complex;
    cv::merge(planes, 2, complex);

    // Compute DFT
    cv::dft(complex, complex);

    // Split real and complex planes (you can reuse the 'planes' array to save
    // the result)
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
    cv::imwrite("./debug/magnitude.png", mag);
    phase.convertTo(phase, CV_8UC1, 255);
    cv::imwrite("./debug/phase.png", phase);

    return true;

}

bool Tools::applyFreqFilter(cv::Mat &input, cv::Mat &output, cv::Mat &filter)
{
    cv::Mat img = input.clone();
    if(img.channels() != 1)
    {
        std::cout << std::endl << "Error: this function is for single channel "
                "grayscale images, channels: " << img.channels();
        return false;
    }

    // Expand the image to an optimal size.
    cv::Mat padded;
    int opt_rows = cv::getOptimalDFTSize(img.rows);
    int opt_cols = cv::getOptimalDFTSize(img.cols);
    cv::copyMakeBorder(img, padded, 0, opt_rows - img.rows, 0,
                       opt_cols - img.cols, cv::BORDER_CONSTANT);

    // Make place for both the real and complex values by merging planes into a
    // cv::Mat with 2 channels.
    // Use float element type because frequency domain ranges are large.
    cv::Mat planes[] = {cv::Mat_<float>(padded),
                        cv::Mat_<float>::zeros(padded.size())};
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

void Tools::debugRandomKernel(cv::Mat &input, size_t kernelSize,
                              size_t x, size_t y)
{
    if( x == 0 && y == 0)
    {
        x = input.cols * std::rand();
        y = input.rows * std::rand();
    }
    // forcing the kernel inside the matrix limits
    x = std::max(std::min(x, input.cols-kernelSize), kernelSize);
    y = std::max(std::min(y, input.cols-kernelSize), kernelSize);

    std::cout << std::endl;
    for(int i = y - (kernelSize/2); i < y + (kernelSize/2); ++i)
    {

        for(size_t j = x - (kernelSize/2); j < x + (kernelSize/2); ++j)
        {
            std::cout << input.at<int>(i, j);
        }
        std::cout << std::endl;
    }

}

cv::Mat Tools::get_histogram(cv::Mat &grey_img){
    // Calculate histogram of a greyscale image.
    cv::Mat histogram;
    int channels[] = {0};
    int dims = 1;
    int bins = 256;
    float range[] = {0, 255};
    const float *ranges[] = {range};
    // Calculate the histogram.
    cv::calcHist(&grey_img, 1, channels, cv::Mat(),
                 histogram, dims, &bins, ranges);
    // Draw the histogram on an image
    cv::Mat hist_img = cv::Mat::ones(2*256, 2*256, CV_8U)*255;
    // Normalize the histogram values accordingly to the histogram image size.
    normalize(histogram, histogram, 0, hist_img.rows, cv::NORM_MINMAX, CV_32F);
    int bin_width = cvRound((double)hist_img.cols/bins);
    for(auto bin_index = 0; bin_index < bins; bin_index++)
        {
            if (bin_index == 255){
                cout << "hist 255: " << histogram.at<float>(1) << "\n";
            }
            float bin_value = cvRound(histogram.at<float>(bin_index));
            rectangle(hist_img, cv::Point(bin_index * bin_width, hist_img.rows),
                      cv::Point((bin_index+1) * bin_width,
                                hist_img.rows - bin_value), 0, 
                                CV_FILLED, 8, 0 );
        }
    return hist_img;
}

cv::Mat Tools::log_transform(cv::Mat &grey_img, int c){
    cv::Mat transformed_img;
    // Copy the input image and use a 32F depth (to store log values).
    grey_img.convertTo(transformed_img, CV_32F);
    cv::log(c*(transformed_img+1), transformed_img);
    normalize(transformed_img, transformed_img, 0, 1, cv::NORM_MINMAX);
    transformed_img *= 255;
    transformed_img.convertTo(transformed_img, CV_8UC1);
    return transformed_img;
}
