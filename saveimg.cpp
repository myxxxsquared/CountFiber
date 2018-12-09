
#include "Count.h"
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

void saveimg(const cv::Mat &img, const char* filename)
{
    double minval, maxval;
    cv::minMaxLoc(img, &minval, &maxval);
    cv::Mat imgsave = (img - minval) * (255/(maxval - minval));
    imgsave.convertTo(imgsave, CV_8UC1);
    cv::cvtColor(imgsave, imgsave, CV_GRAY2BGR);
    cv::imwrite(filename, imgsave);
}
