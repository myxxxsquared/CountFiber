
#include "Count.h"

void GenKernel(cv::Mat &kernel)
{
    int ksize = 30;
    int ksizea = 2*ksize+1;
    int r02 = 14*14;


    kernel.create(ksizea, ksizea, CV_32FC1);
    for(int i = 0; i < ksizea; ++i)
    {
        for(int j = 0; j < ksizea; ++j)
        {
            int r2 = (i - ksize)*(i - ksize) + (j - ksize)*(j - ksize);
            kernel.at<float>(j, i) = (r02-r2)*std::exp(-r2/(float)r02)/r02;
        }
    }
    kernel -= cv::mean(kernel).val[0];
    saveimg(kernel, "kernel.jpg");
}
