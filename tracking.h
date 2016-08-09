#ifndef TRACKING_H
#define TRACKING_H

#include <QMainWindow>

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include "opencv2/video/tracking.hpp"
#include <opencv2/core/utility.hpp>
#include "opencv2/videoio.hpp"
#include <QTime>

class Tracking
{
public:
    Tracking();
    cv::Mat thresholdUsingHSVColourSpace(cv::Mat originalImg,int h, int s, int v);
    QImage selectedObjectImg(cv::Mat originalImg, cv::Rect selection);
    QImage selectedObjectHist(cv::Rect selection);
    cv::Rect trackObject();
    QVector<QVector2D> calculateObjectCenter();

    cv::Mat getHue() const;
    void setHue(const cv::Mat &value);

    cv::Mat getThresholdedImg() const;
    void setThresholdedImg(const cv::Mat &value);

    cv::Rect getTrackWindow() const;
    void setTrackWindow(const cv::Rect &value);

    cv::Mat getHist() const;
    void setHist(const cv::Mat &value);

    cv::Rect getTrackBox() const;
    void setTrackBox(const cv::Rect &value);

    const float *getPhranges() const;
    void setPhranges(const float *value);

private:
    cv::Mat originalInput;
    cv::Mat hue;
    cv::Mat thresholdedImg;
    cv::Rect trackWindow;
    cv::Mat histimg;
    cv::Mat hist;
    cv::Rect trackBox;
    cv::Mat backproj;
};

#endif // TRACKING_H
