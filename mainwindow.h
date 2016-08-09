#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include "opencv2/video/tracking.hpp"
#include <opencv2/core/utility.hpp>
#include "opencv2/videoio.hpp"
#include <QTime>

#include "tracking.h"
#include "predictions.h"
//using namespace cv;
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void updateGUI();

private slots:
    void pauseResumeButtonLogic();
    void setValuesAccordingToButton();
    void removeSelectionLogic();
    void displayGraphButton();
    void drawActualAndPredictedPaths();
    bool eventFilter(QObject *obj, QEvent *event);
    void setValuesForRed();
    void setValuesForBlue();


private:
    Ui::MainWindow *ui;

    cv::VideoCapture input;
    cv::Mat originalInput;
    cv::Mat processedInput;

    bool mousePressed;

    cv::Mat thresholdResults;

    cv::Rect selection;

    Tracking t;
    Predictions p;

    cv::Rect trackWindow;
    cv::RotatedRect trackBox;
    bool codeExecuted;

    float previousXPrediction;
    float previousYPrediction;

    int counterUsedForPlot;
    QVector<double> xPlotValues;
    QVector<double> yPlotValues;

    int counter;

    QVector<QVector2D> weightedAveragePrediction(QVector<QVector2D> listOfPoints);
    QVector<QVector2D> averagePrediction(QVector<QVector2D> listOfPoints);
    QVector2D predictionUsingKalmanFilter(QVector<QVector2D> listOfPoints);
    void init_KalmanFilterParameters(float currentX, float currentY);
    void calculateAccuracyAndPlotGraph(float centerX, float centerY);


    bool displayGraphBool;

    int counterForKalmanFilterOnly;

    bool kalmanInitBool;

    QVector<QVector2D> weightedPredictionResults;
    QVector<QVector2D> averaPredictionResults;
    QVector<QVector2D> kalmanFilterResults;

    QVector<QVector2D> listOfPoints;

    QImage QimgOriginalInput;
    QImage QimgProcessedInput;
    QImage QimgHistIm;
    QImage QimgSelectedObject;

    vector<cv::Vec3f> circleStorage;
    vector<cv::Vec3f>::iterator cIterator;

    QPoint point1;
    QPoint point2;

    int clickCount;

    QTimer* timerControl;

    void MainWindow::exitProgram();
};

#endif // MAINWINDOW_H
