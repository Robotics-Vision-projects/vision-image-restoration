
#include <iostream>

#include <tools.h>

int foo()
{
    return 2;
}

int main(int argc, char** agrv)
{
    //std::cout << foo2();
    std::cout << Tools::frequency_analysis(cv::Mat());
    return 0;

}
