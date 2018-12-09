#include "Count.h"


void NMI(const cv::Mat &filteredimg, std::vector<cv::Point2i> &maxpoints, int width, int height)
{
    int areawidth = 17;
    int halfareawidth = (areawidth-1)/2;
    float th = 30;

    for(int i = 0; i < height; i += areawidth)
    {
        for(int j = 0; j < width; j += areawidth)
        {
            cv::Rect roi{
                cv::Point2i(std::max(0, j), std::max(0, i)),
                cv::Point2i(std::min(width, j+areawidth), std::min(height, i+areawidth))};
            double minval, maxval;
            cv::Point2i minloc, maxloc, newmaxloc;
            cv::minMaxLoc(filteredimg(roi), &minval, &maxval, &minloc, &maxloc);
            maxloc.x += j;
            maxloc.y += i;
            cv::Rect new_roi{
                cv::Point2i(std::max(0, maxloc.x-halfareawidth), std::max(0, maxloc.y-halfareawidth)),
                cv::Point2i(std::min(width, maxloc.x+halfareawidth+1), std::min(height, maxloc.y+halfareawidth+1))};
            cv::minMaxLoc(filteredimg(new_roi), &minval, &maxval, &minloc, &newmaxloc);
            if(newmaxloc.x+new_roi.x == maxloc.x && newmaxloc.y+new_roi.y == maxloc.y && filteredimg.at<float>(maxloc) >= th)
            {
                maxpoints.push_back(maxloc);
            }
        }
    }
}
