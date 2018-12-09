
#include "Count.h"
#include "FiberInfo.h"

#include <queue>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

void GetFiberInfo(cv::Mat &nearestmat, const std::vector<cv::Point2i> &maxpoints, const cv::Mat &grayimg, std::vector<FiberInfo> &infos, int width, int height)
{
    infos.resize(maxpoints.size());

    #pragma omp parallel for
    for(int i = 0; i < maxpoints.size(); ++i)
    {
        const cv::Point2i &pt = maxpoints[i];
        std::queue<cv::Point2i> search_queue;
        search_queue.push(pt);

        FiberInfo info;
        info.x = pt.x;
        info.y = pt.y;

        while(!search_queue.empty())
        {
            cv::Point2i curpt = search_queue.front();
            search_queue.pop();

            if(curpt.x < 0 || curpt.x >= width || curpt.y < 0 || curpt.y >= height)
                continue;
            int &curptval = nearestmat.at<int>(curpt);
            if(curptval != i)
                continue;

            curptval += maxpoints.size();
            ++info.num_pixel;
            info.avg_x += curpt.x;
            info.avg_y += curpt.y;
            info.avg_clr += grayimg.at<float>(curpt);

            search_queue.push(cv::Point2i(curpt.x - 1, curpt.y));
            search_queue.push(cv::Point2i(curpt.x + 1, curpt.y));
            search_queue.push(cv::Point2i(curpt.x, curpt.y - 1));
            search_queue.push(cv::Point2i(curpt.x, curpt.y + 1));
        }

        if(info.num_pixel == 0)
        {
            info.avg_x = info.x;
            info.avg_y = info.y;
        }
        else
        {
            info.avg_x /= info.num_pixel;
            info.avg_y /= info.num_pixel;
            info.avg_clr /= info.num_pixel;
        }

        infos[i] = info;
    }

    cv::Vec3b colors[] = {
        cv::Vec3b(0, 255, 255),
        cv::Vec3b(255, 0, 0),
        cv::Vec3b(0, 255, 0),
        cv::Vec3b(0, 0, 255),
        cv::Vec3b(255, 255, 0),
        cv::Vec3b(255, 0, 255),
        cv::Vec3b(0, 0, 0)
    };

    cv::Mat fiber_show;
    fiber_show.create(height, width, CV_8UC3);
    #pragma omp parallel for
    for(int i = 0; i < height; ++i)
    {
        for(int j = 0; j < width; ++j)
        {
            int idx = nearestmat.at<int>(i, j);
            if(idx <= (int)maxpoints.size())
                fiber_show.at<cv::Vec3b>(i, j) = colors[6];
            else
                fiber_show.at<cv::Vec3b>(i, j) = colors[(nearestmat.at<int>(i, j)-maxpoints.size()) % 6];
        }
    }
    for(int i = 0; i < (int)maxpoints.size(); ++i)
        cv::circle(fiber_show, maxpoints[i], 3, cv::Scalar(255, 255, 255), -1);
    cv::imwrite("fiber_show.jpg", fiber_show);
}
