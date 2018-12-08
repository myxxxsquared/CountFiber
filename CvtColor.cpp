
#include "Count.h"

#include <opencv2/imgproc.hpp>

void CvtColor(cv::Mat &img, cv::Mat &grayimg)
{
    cv::cvtColor(img, grayimg, CV_BGR2GRAY);
    grayimg.convertTo(grayimg, CV_32FC1);
}

