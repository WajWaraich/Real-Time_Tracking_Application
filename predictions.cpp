#include "predictions.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QtCore>
#include<QMessageBox>
#include<QPainter>

using namespace cv;

Predictions::Predictions()
{

}

QVector<QVector2D> Predictions::weightedAveragePrediction(QVector<QVector2D> listOfPoints){


    /*=============================================================================
     | Predicting using weighted average approach, essentially all this function does
     | is to add higher weight to the most recent positions of the object and calculate
     | an average by simply adding all of them together and dividing it by the number of
     | weights
     *===========================================================================*/

    QVector<QVector2D> prediction;

    float totalXDiff =  (((listOfPoints.at(listOfPoints.size()-1).x()-listOfPoints.at(listOfPoints.size()-2).x())*8)+
                         ((listOfPoints.at(listOfPoints.size()-2).x()-listOfPoints.at(listOfPoints.size()-3).x())*7)+
                         ((listOfPoints.at(listOfPoints.size()-3).x()-listOfPoints.at(listOfPoints.size()-4).x())*6)+
                         ((listOfPoints.at(listOfPoints.size()-4).x()-listOfPoints.at(listOfPoints.size()-5).x())*5)+
                         ((listOfPoints.at(listOfPoints.size()-5).x()-listOfPoints.at(listOfPoints.size()-6).x())*4)+
                         ((listOfPoints.at(listOfPoints.size()-6).x()-listOfPoints.at(listOfPoints.size()-7).x())*3)+
                         ((listOfPoints.at(listOfPoints.size()-7).x()-listOfPoints.at(listOfPoints.size()-8).x())*2)+
                         ((listOfPoints.at(listOfPoints.size()-8).x()-listOfPoints.at(listOfPoints.size()-9).x())*1));

    float totalYDiff =  (((listOfPoints.at(listOfPoints.size()-1).y()-listOfPoints.at(listOfPoints.size()-2).y())*8)+
                         ((listOfPoints.at(listOfPoints.size()-2).y()-listOfPoints.at(listOfPoints.size()-3).y())*7)+
                         ((listOfPoints.at(listOfPoints.size()-3).y()-listOfPoints.at(listOfPoints.size()-4).y())*6)+
                         ((listOfPoints.at(listOfPoints.size()-4).y()-listOfPoints.at(listOfPoints.size()-5).y())*5)+
                         ((listOfPoints.at(listOfPoints.size()-5).y()-listOfPoints.at(listOfPoints.size()-6).y())*4)+
                         ((listOfPoints.at(listOfPoints.size()-6).y()-listOfPoints.at(listOfPoints.size()-7).y())*3)+
                         ((listOfPoints.at(listOfPoints.size()-7).y()-listOfPoints.at(listOfPoints.size()-8).y())*2)+
                         ((listOfPoints.at(listOfPoints.size()-8).y()-listOfPoints.at(listOfPoints.size()-9).y())*1));

    float absoluteTotalXDiff = (float)totalXDiff/20;
    float absoluteTotalYDiff = (float)totalYDiff/20;

    float predictionX = listOfPoints.at(listOfPoints.size()-1).x() + absoluteTotalXDiff;
    float predictionY = listOfPoints.at(listOfPoints.size()-1).y() + absoluteTotalYDiff;


    prediction.append(QVector2D(predictionX,predictionY));

    return prediction;

}

QVector<QVector2D> Predictions::averagePrediction(QVector<QVector2D> listOfPoints){

    /*=============================================================================
     | This is simply a moving average approach, it simply takes the listOfPoints and
     | just calculates an average for it and returns that average as a prediction for
     | the next point
     *===========================================================================*/

    QVector<QVector2D> prediction;

    float totalCenterXPrediction=0;
    float totalCenterYPrediction=0;

    for(int i=0; i<listOfPoints.size(); i++){
        totalCenterXPrediction += listOfPoints.at(i).x();
        totalCenterYPrediction += listOfPoints.at(i).y();
    }

    float centerXPrediction = totalCenterXPrediction/10;
    float centerYPrediction = totalCenterYPrediction/10;

    prediction.append(QVector2D(centerXPrediction,centerYPrediction));

    return prediction;

}

QVector2D Predictions::predictionUsingKalmanFilter(QVector<QVector2D> listOfPoints){

    /*=============================================================================
     | This is using the Kalman Filter approach, it simply takes a single point as
     | an input and adds it to the kalmanFilterVar and predicts the next point by
     | using the correct() method, the Kalman filter is more like a noise reducing
     | filter, it is usually used for noisy signals, i.e. an object moving erratically
     | and produces a predicted position in respects to the overall motion of the object
     | it is an extremly powerful filter which can be used for prediction various things
     |
     | The code below was insipired and parts were copied from the following link:
     | http://opencvexamples.blogspot.com/2014/01/kalman-filter-implementation-tracking.html
     *===========================================================================*/

    QVector2D prediction2;

    Mat_<float> measurement(2,1);
    measurement.setTo(Scalar(0));

    Mat prediction = kalmanFilterVar.predict();
    Point predictPt(prediction.at<float>(0),prediction.at<float>(1));

    measurement(0) = listOfPoints.at(9).x();
    measurement(1) = listOfPoints.at(9).y();

    Point measPt(measurement(0),measurement(1));

    Mat estimated = kalmanFilterVar.correct(measurement);


    float predictionX = estimated.at<float>(0);
    float predictionY = estimated.at<float>(1);

    prediction2.setX(predictionX);
    prediction2.setY(predictionY);

    return prediction2;
}


void Predictions::init_KalmanFilterParameters(float currentX, float currentY){

    /*=============================================================================
     | Initialising the states/variables needed for kalman filtering prediction
     *===========================================================================*/
    kalmanFilterVar.init(4,2,0);


    kalmanFilterVar.transitionMatrix = (Mat_<float>(4, 4) << 1,0,1,0,   0,1,0,1,  0,0,1,0,  0,0,0,1);


    kalmanFilterVar.statePre.at<float>(0) = currentX;
    kalmanFilterVar.statePre.at<float>(1) = currentY;
    kalmanFilterVar.statePre.at<float>(2) = 0;
    kalmanFilterVar.statePre.at<float>(3) = 0;

    setIdentity(kalmanFilterVar.measurementMatrix);
    setIdentity(kalmanFilterVar.processNoiseCov, Scalar::all(1e-4));
    setIdentity(kalmanFilterVar.measurementNoiseCov, Scalar::all(1e-1));
    setIdentity(kalmanFilterVar.errorCovPost, Scalar::all(.1));

}

