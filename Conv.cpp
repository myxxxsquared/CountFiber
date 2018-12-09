
#include "Count.h"

#include <opencv2/imgproc.hpp>

void Conv(const cv::Mat &avgimage, cv::Mat &filteredimg, const cv::Mat &kernel)
{
    cv::filter2D(avgimage, filteredimg, -1, kernel);
    saveimg(filteredimg, "filteredimg.jpg");
}
