
#include "Count.h"
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

void ShowResult(std::vector<cv::Point2i> &maxpoints, cv::Mat &img)
{
    cv::Mat img_final = img.clone();
    for(int i = 0; i < (int)maxpoints.size(); ++i)
        cv::circle(img_final, maxpoints[i], 10, cv::Scalar(0, 0, 255), -1);
    cv::imwrite("img_final.jpg", img_final);
}

