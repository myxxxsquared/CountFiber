
#include "Count.h"
#include <opencv2/highgui.hpp>
#include <opencv2/flann.hpp>
#include <opencv2/imgproc.hpp>

void GenNearestMat(cv::Mat &nearestmat, cv::Mat &avgimage, std::vector<cv::Point2i> &maxpoints, int width, int height)
{
    float th = 100;

    nearestmat.create(height, width, CV_32SC1);

    cv::Mat_<float> features(0,2);
    for(auto & point : maxpoints) {
        cv::Mat row = (cv::Mat_<float>(1, 2) << point.x, point.y);
        features.push_back(row);
    }
    cv::flann::Index flann_index(features, cv::flann::KDTreeIndexParams(1));

    for(int i = 0; i < height; ++i)
    {
        for(int j = 0; j < width; ++j)
        {
            if(avgimage.at<float>(i, j) < th)
            {
                nearestmat.at<int>(i, j) = -1;
                continue;
            }
            cv::Mat query = (cv::Mat_<float>(1, 2) << (float)j, (float)i);
            cv::Mat indices, dists;
            flann_index.knnSearch(query, indices, dists, 1);
            int mindist = indices.at<int>(0);
            nearestmat.at<int>(i, j) = mindist;
        }
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

    cv::Mat mindist_show;
    mindist_show.create(height, width, CV_8UC3);
    for(int i = 0; i < height; ++i)
    {
        for(int j = 0; j < width; ++j)
        {
            int idx = nearestmat.at<int>(i, j);
            if(idx == -1)
                mindist_show.at<cv::Vec3b>(i, j) = colors[6];
            else
                mindist_show.at<cv::Vec3b>(i, j) = colors[nearestmat.at<int>(i, j) % 6];
        }
    }
    for(int i = 0; i < (int)maxpoints.size(); ++i)
        cv::circle(mindist_show, maxpoints[i], 3, cv::Scalar(255, 255, 255), -1);
    cv::imwrite("mindist_show.jpg", mindist_show);
}
