#include "tracking.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QtCore>
#include<QMessageBox>
#include<QPainter>

using namespace cv;

Tracking::Tracking()
{
}

Mat Tracking::thresholdUsingHSVColourSpace(cv::Mat originalImg, int h, int s, int v)
{

    /*=============================================================================
     | Thresholding using the values given by the sliders, the main function call
     | is the inRange() one which deals with the thresholding the originalImg
     *===========================================================================*/

    Mat thresholdingResult;

    cvtColor(originalImg, originalImg, CV_BGR2HSV);

    hue.create(originalImg.size(), originalImg.depth());

    int ch[] = {0, 0};
    mixChannels(&originalImg, 1, &hue, 1, ch, 1);

    inRange(originalImg, Scalar(0, v, MIN(h,s)),
            Scalar(180, 256, MAX(h, s)), thresholdingResult);

    setThresholdedImg(thresholdingResult);

    return thresholdingResult;
}

QImage Tracking::selectedObjectImg(Mat originalImg, Rect selection){


    /*=============================================================================
     | Returning a QImage based on the selection, simply using the constructor
     | for Mat() to crop the img and converting it to the correct colour-space
     *===========================================================================*/

    Mat objectOriginalImage(originalImg,selection);

    cvtColor(objectOriginalImage, objectOriginalImage, CV_HSV2RGB);

    QImage QimgSelectedObject ((uchar*)objectOriginalImage.data, objectOriginalImage.cols, objectOriginalImage.rows, objectOriginalImage.step, QImage::Format_RGB888);

    return QimgSelectedObject;
}

QImage Tracking::selectedObjectHist(Rect selection){


    /*=============================================================================
     | Producing a histogram image and a Mat() with the histogram values of the selected
     | object/region.
     *===========================================================================*/

    int hsize = 16;
    float hranges[] = {0,180};
    const float* phranges = hranges;

    Mat roi(hue, selection), maskroi(thresholdedImg, selection);

    calcHist(&roi, 1, 0, maskroi, hist, 1, &hsize, &phranges);
    normalize(hist, hist, 0, 255, NORM_MINMAX);

    histimg = Mat::zeros(200, 320, CV_8UC3);
    histimg = Scalar::all(0);

    int binW = histimg.cols / hsize;
    Mat buf(1, hsize, CV_8UC3);
    for( int i = 0; i < hsize; i++ ){
        buf.at<Vec3b>(i) = Vec3b(saturate_cast<uchar>(i*180./hsize), 255, 255);
    }
    cvtColor(buf, buf, COLOR_HSV2RGB);

    for( int i = 0; i < hsize; i++ )
    {
        int val = saturate_cast<int>(hist.at<float>(i)*histimg.rows/255);
        rectangle( histimg, Point(i*binW,histimg.rows),
                   Point((i+1)*binW,histimg.rows - val),
                   Scalar(buf.at<Vec3b>(i)), -1, 8 );
    }

    setHist(hist);
    QImage QimgHistImg ((uchar*)histimg.data, histimg.cols, histimg.rows, histimg.step, QImage::Format_RGB888);
    return QimgHistImg;
}


Rect Tracking::trackObject(){

    /*=============================================================================
     | Tracking the selected region, the region is obtained by the trackWindow
     | member variable wherein the selection has been stored, this code simply
     | calculates the camshift (OpenCV advanced meanshift) and returns a Rect()
     | position of the object
     *===========================================================================*/

    float hranges[] = {0,180};
    const float* phranges = hranges;

    calcBackProject(&hue, 1, 0, hist, backproj, &phranges);

    backproj &= thresholdedImg;

    RotatedRect trackBox = CamShift(backproj, trackWindow,
                                    TermCriteria( TermCriteria::EPS | TermCriteria::COUNT, 10, 1 ));

    if( trackWindow.area() <= 1 )
    {
        int cols = backproj.cols, rows = backproj.rows, r = (MIN(cols, rows) + 5)/6;
        trackWindow = Rect(trackWindow.x - r, trackWindow.y - r,
                           trackWindow.x + r, trackWindow.y + r) &
                Rect(0, 0, cols, rows);
    }

    setTrackBox(trackBox.boundingRect());

    return trackBox.boundingRect();
}

QVector<QVector2D> Tracking::calculateObjectCenter(){

    /*=============================================================================
     | Code to calculate the center of the bounding box
     *===========================================================================*/

    float centerX = getTrackBox().x + (0.5*getTrackBox().width);
    float centerY = getTrackBox().y + (0.5*getTrackBox().height);

    QVector<QVector2D> results;

    results.append(QVector2D(centerX,centerY));

    return results;
}

cv::Mat Tracking::getHue() const
{
    return hue;
}

void Tracking::setHue(const cv::Mat &value)
{
    hue = value;
}

cv::Mat Tracking::getThresholdedImg() const
{
    return thresholdedImg;
}

void Tracking::setThresholdedImg(const cv::Mat &value)
{
    thresholdedImg = value;
}

cv::Rect Tracking::getTrackWindow() const
{
    return trackWindow;
}

void Tracking::setTrackWindow(const cv::Rect &value)
{
    trackWindow = value;
}

cv::Mat Tracking::getHist() const
{
    return hist;
}

void Tracking::setHist(const cv::Mat &value)
{
    hist = value;
}

cv::Rect Tracking::getTrackBox() const
{
    return trackBox;
}

void Tracking::setTrackBox(const cv::Rect &value)
{
    trackBox = value;
}

