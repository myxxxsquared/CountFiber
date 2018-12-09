
#include "Count.h"

void AvgColor(const cv::Mat &grayimg, cv::Mat &avgimage, int width, int height)
{
    int avgrange = 30;
    int calcrange = 30;
    int avgrangea = avgrange+calcrange+1;

    avgimage = grayimg.clone();
    for(int i = 0; i < height; i += avgrange)
    {
        for(int j = 0; j < width; j += avgrange)
        {
            cv::Rect roi{
                cv::Point2i(std::max(0, j-calcrange), std::max(0, i-calcrange)),
                cv::Point2i(std::min(width, j+avgrangea), std::min(height, i+avgrangea))};
            float avg = cv::mean(grayimg(roi)).val[0];
            cv::Rect roi_copy{
                cv::Point2i(j, i),
                cv::Point2i(std::min(width, j+avgrange), std::min(height, i+avgrange))};
            avgimage(roi_copy) = grayimg(roi_copy) * (3.0f + 255.0f / avg);
            // avgimage(roi_copy) = grayimg(roi_copy) * 0 + avg;
        }
    }
    double minval, maxval;
    cv::minMaxLoc(avgimage, &minval, &maxval);
    avgimage = avgimage * (1/maxval);
    saveimg(avgimage, "avg.jpg");
}
