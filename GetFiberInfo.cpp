
#include "Count.h"
#include "FiberInfo.h"

#include <queue>

void GetFiberInfo(cv::Mat &nearestmat, std::vector<cv::Point2i> &maxpoints, cv::Mat &grayimg, std::vector<FiberInfo> &infos, int width, int height)
{
    for(int i = 0; i < maxpoints.size(); ++i)
    {
        cv::Point2i &pt = maxpoints[i];
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

            curptval = -1;
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

        infos.push_back(info);
    }
}
