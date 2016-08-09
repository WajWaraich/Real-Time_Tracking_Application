#ifndef PREDICTIONS_H
#define PREDICTIONS_H

#include <QMainWindow>

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include "opencv2/video/tracking.hpp"
#include <opencv2/core/utility.hpp>
#include "opencv2/videoio.hpp"
#include <QTime>

class Predictions
{
public:
    Predictions();
    QVector<QVector2D> weightedAveragePrediction(QVector<QVector2D> listOfPoints);
    QVector<QVector2D> averagePrediction(QVector<QVector2D> listOfPoints);
    QVector2D predictionUsingKalmanFilter(QVector<QVector2D> listOfPoints);
    void init_KalmanFilterParameters(float currentX, float currentY);

private:
    cv::KalmanFilter kalmanFilterVar;

};

#endif // PREDICTIONS_H
