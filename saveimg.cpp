
#include "Count.h"
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

void saveimg(cv::Mat img, const char* filename)
{
    double minval, maxval;
    cv::minMaxLoc(img, &minval, &maxval);
    img = (img - minval) * (255/(maxval - minval));
    img.convertTo(img, CV_8UC1);
    cv::cvtColor(img, img, CV_GRAY2BGR);
    cv::imwrite(filename, img);
}
