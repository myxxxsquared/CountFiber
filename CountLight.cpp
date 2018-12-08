
#include <vector>
#include <opencv2/highgui.hpp>

#include "Count.h"
#include "FiberInfo.h"

void CvtColor(cv::Mat &img, cv::Mat &grayimg);
void AvgColor(cv::Mat &grayimg, cv::Mat &avgimage, int width, int height);
void GenKernel(cv::Mat &kernel);
void Conv(cv::Mat &avgimage, cv::Mat &filteredimg, cv::Mat &kernel);
void NMI(cv::Mat &filteredimg, std::vector<cv::Point2i> &maxpoints, int width, int height);
void ShowResult(std::vector<cv::Point2i> &maxpoints, cv::Mat &img);
void GenNearestMat(cv::Mat &nearestmat, cv::Mat &avgimage, std::vector<cv::Point2i> &maxpoints, int width, int height);
void GetFiberInfo(cv::Mat &nearestmat, std::vector<cv::Point2i> &maxpoints, cv::Mat &grayimg, std::vector<FiberInfo> &infos, int width, int height);
void SaveToTTree(std::vector<FiberInfo> &infos);

int main()
{
    cv::Mat img, grayimg, avgimage, kernel, filteredimg;
    std::vector<cv::Point2i> maxpoints;

    img = cv::imread("count.jpg");

    int width = img.cols;
    int height = img.rows;

    // 转换颜色
    CvtColor(img, grayimg);

    // 增强暗区对比度
    AvgColor(grayimg, avgimage, width, height);

    // 生成卷积核
    GenKernel(kernel);

    // 卷积
    Conv(avgimage, filteredimg, kernel);

    // 非最大抑制
    NMI(filteredimg, maxpoints, width, height);

    // 输出结果
    ShowResult(maxpoints, img);

    printf("points: %ld\n", maxpoints.size());

    cv::Mat nearestmat;
    std::vector<FiberInfo> infos;
    GenNearestMat(nearestmat, avgimage, maxpoints, width, height);
    GetFiberInfo(nearestmat, maxpoints, grayimg, infos, width, height);
    SaveToTTree(infos);

    return 0;
}
