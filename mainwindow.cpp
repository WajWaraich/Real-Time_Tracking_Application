#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tracking.h"


#include<QtCore>
#include<QMessageBox>
#include<QPainter>
#include "qcustomplot.h"

using namespace cv;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /*=============================================================================
     | Constructor used to open up the webcam, also to check whether a
     | valid webcam is attached, if there's more than one webcam attached then
     | the parameter for open() can be changed to point towards the correct one
     *===========================================================================*/
    input.open(0);

    if(input.isOpened()==false){
        ui->plainTextEdit->appendPlainText("Webcam was not read properly!");
    }

    counterUsedForPlot=0; //Specific counter which is used for resetting the plot


    /*=============================================================================
     | Initialising a QTimer and calling the updateGUI function every 20ms, instead
     | of a QTimer threads could have been used in this step, but due to understanding
     | QTimer better than threads I opted for QTimer
     *===========================================================================*/
    timerControl = new QTimer(this);
    connect(timerControl,SIGNAL(timeout()),this,SLOT(updateGUI()));
    timerControl->start(20);
}

void MainWindow::updateGUI()
{

    /*=============================================================================
     | the updateGUI() function is called every frame to read each frame and to
     | process it accordingly
     *===========================================================================*/
    input.read(originalInput);

    if(originalInput.empty()==true)
        return;


    /*=============================================================================
     | The sliders in the GUI are used to capture the values that are used for thresholding
     *===========================================================================*/

    int h = ui->vmin->value();
    int s = ui->vmax->value();
    int v = ui->smin->value();

    /*=============================================================================
     | The slider values are passed onto the thresholding() function which is
     | inside the tracking class - which deals with thresholding the frame and returns
     | a binary image
     *===========================================================================*/
    thresholdResults = t.thresholdUsingHSVColourSpace(originalInput,h,s,v);


    /*=============================================================================
     | The clickCount just ensures that when the mouse button is pressed on the label
     | this if statement only runs once, this is just to ensure that the object that is
     | picked is the object that is tracked throughout the frames, of course when the
     | user presses the mousebutton again to select another object the clickCount is
     | assigned a value of -1 in which case this if statement runs again and everything
     | changes according to the new object
     *===========================================================================*/
    if(clickCount<0)
    {
        selection = Rect(Point(point1.x(),point1.y()),Point(point2.x(),point2.y()));

        t.setTrackWindow(selection);

        clickCount=1; //Ensures that this if statement is only run once when the mousebutton is pressed


        /*=============================================================================
         | Functions inside the tracking class are called for getting the histogram for
         | selected object/region and a cropped image is also extracted for displaying
         | purposes, both functions return QImages so it can be directly inserted into a
         | Pixmap/Label
         *===========================================================================*/
        QImage QimgHistImg = t.selectedObjectHist(selection);
        ui->label_5->setPixmap(QPixmap::fromImage(QimgHistImg));

        QImage QselectedObjectImg = t.selectedObjectImg(originalInput,selection);
        ui->label_4->setPixmap(QPixmap::fromImage(QselectedObjectImg));

        codeExecuted = true; //variable used for initialsing the tracking and predicting sequence in the next if statement
        counter=1; //frame counter
        counterForKalmanFilterOnly=0; //Specific counter for kalman filtering
        listOfPoints.clear(); //Clearing anything that might be stored previously from an object inside the member variable

        kalmanInitBool=false; //used for initialising the kalmanfilter variables, ensures that the call to the function only goes out once
    }



    /*=============================================================================
     | This if statement is executed when an object has been selected by the user,
     | the main operation of the body of this if statement is to combine the tracking,
     | predictions and accuracy componenets of this application, it uses both
     | the tracking and prediction classes to extract the required data, additionally
     | a call is also made to the drawActualAndPredictedPaths() function to visually
     | show the results
     *===========================================================================*/
    if(codeExecuted==true)
    {
        ui->enableDisableGraphBtn->setEnabled(true); //Graph button is enabled as an object has been picked


        /*=============================================================================
         | The openCV function rectangle is used to draw the bounding box around the
         | tracked object, the Rect() (coordinates) for drawing the bounding box
         | are retrieved from the tracking class by calling this trackObject() function
         *===========================================================================*/
        rectangle(originalInput, t.trackObject(), Scalar(0,0,255),2, 8, 0);

        QVector<QVector2D> centerPositions = t.calculateObjectCenter(); //Calculating the center coordinates
        //of the bounding box by calling the calculateObjectCenter() function

        float centerX = centerPositions.at(0).x(); //initialising the center x and y coordinates variables
        float centerY = centerPositions.at(0).y();

        circle(originalInput,Point(centerX, centerY),3,Scalar(0,255,0),-1); //Drawing a filled circle in the center of the bounding box

        /*=============================================================================
         | The following if statement is only executed once 10 frames have passed
         | the reason is because the predictions are based on 10 frames, at least
         | 10 points are needed inside listOfPoints for the predictions
         *===========================================================================*/
        if(counter>10)
        {
            QVector<QVector2D> tempList; //temp vector initialised

            for(int i=1; i<listOfPoints.size(); i++) //looping through all the points inside listOfPoints
                tempList.append(listOfPoints.at(i)); //the purpose of this is to shift the points
                                                     //the last point index(0) is discarded

            tempList.append(QVector2D(centerX,centerY)); //the current point of the object is added to the tempList

            listOfPoints = tempList; //then simply the listOfPoints is replaced by the tempList which contains the shiftted points

            /*=============================================================================
             | The radio buttons are checked to see whether any of them have been checked
             | if they have been checked their corresponding prediction functions are called
             | which are inside the predictions class, the results are saved inside member
             | variables to be used later
             *===========================================================================*/
            if(ui->radioButton_2->isChecked()){
                weightedPredictionResults = p.weightedAveragePrediction(listOfPoints);
                ui->radioButton->setChecked(false);
                ui->radioButton_3->setChecked(false);
            }
            if(ui->radioButton->isChecked()){
                averaPredictionResults = p.averagePrediction(listOfPoints);
                ui->radioButton_2->setChecked(false);
                ui->radioButton_3->setChecked(false);
            }

            if(ui->radioButton_3->isChecked()){
                if(kalmanInitBool==false){ //ensures the the states are only intialised once
                    p.init_KalmanFilterParameters(centerX, centerY);
                    kalmanInitBool=true;
                }

                /*=============================================================================
                 | Due to the nature of a kalman filter it was decided to let another 10 frames
                 | pass before displaying the predictions, the kalman filter is usually used for
                 | reducing noise in a signal and as a result it was decided to let it run for a
                 | further 10 frames, this also allowed a better trail/path to be displayed
                 | for the kalman filter results
                 *===========================================================================*/
                if(counterForKalmanFilterOnly>10){
                    QVector<QVector2D> temp;

                    for(int i=1; i<kalmanFilterResults.size(); i++)
                        temp.append(kalmanFilterResults.at(i));

                    temp.append(p.predictionUsingKalmanFilter(listOfPoints));

                    kalmanFilterResults = temp;
                }

                else
                    kalmanFilterResults.append(p.predictionUsingKalmanFilter(listOfPoints));

                ui->radioButton->setChecked(false);
                ui->radioButton_2->setChecked(false);

                counterForKalmanFilterOnly++;
            }



            ui->plainTextEdit->appendPlainText(QString("---------------------------------------------------------"));

            ui->plainTextEdit->appendPlainText(QString("PREDICTED:     ") + QString("x: ") + QString::number(previousXPrediction) + "    y: " + QString::number(previousYPrediction));

            drawActualAndPredictedPaths(); //Drawing both the actual and predicted paths


            /*=============================================================================
             | If any of the radio buttons are checked then the program needs to calculate
             | the accuracy of the prediction and this is done by using the calculateAccuracyAndPlotGraph()
             | function - however if the graph is disabled using the button then this function
             | will not be executed, the reason this button was added was because drawing the plot
             | is quite demanding and adds a small lag in the program
             *===========================================================================*/
            if(ui->radioButton->isChecked() || ui->radioButton_2->isChecked() || ui->radioButton_3->isChecked()){

                if(displayGraphBool==true){
                    calculateAccuracyAndPlotGraph(centerX, centerY);
                    counterUsedForPlot++;
                }
            }


            /*=============================================================================
             | The predictions need to be saved in order to calculate the accuracy of the
             | predictions and the code below does exactly that, it stores the the prediction
             | in a variable and that variable is used in the next frame to see how accurate the
             | prediction was
             *===========================================================================*/

            if(ui->radioButton->isChecked()){
                previousXPrediction = averaPredictionResults.at(0).x();
                previousYPrediction = averaPredictionResults.at(0).y();
            }

            if(ui->radioButton_2->isChecked()){
                previousXPrediction = weightedPredictionResults.at(0).x();
                previousYPrediction = weightedPredictionResults.at(0).y();
            }

            if(ui->radioButton_3->isChecked()){
                if(counterForKalmanFilterOnly>10){
                    previousXPrediction = kalmanFilterResults.at(9).x();
                    previousYPrediction = kalmanFilterResults.at(9).y();
                }
            }
        }

        else
            listOfPoints.append(QVector2D(centerX,centerY));

        ui->plainTextEdit->appendPlainText(QString("ACTUAL:     ") + QString("x: ") + QString::number(centerX) + "    y: " + QString::number(centerY));
        counter++;
    }

    else
        ui->enableDisableGraphBtn->setEnabled(false); //ensuring that the graph button is only available once a selection has been made



    /*=============================================================================
     | Finally the results are simply displayed for both the original image and
     | the processed image
     *===========================================================================*/
    cvtColor(originalInput, originalInput, CV_HSV2RGB);
    QImage QimgOriginalInput((uchar*)originalInput.data, originalInput.cols, originalInput.rows, originalInput.step, QImage::Format_RGB888);
    QImage QimgProcessedInput((uchar*)thresholdResults.data, thresholdResults.cols, thresholdResults.rows, thresholdResults.step, QImage::Format_Indexed8);

    Scalar color = Scalar( 0, 255, 0);

    if(point2.x()!=0 && point2.y()!=0 && codeExecuted!=true)
        rectangle(originalInput,Point(point1.x(),point1.y()),Point(point2.x(),point2.y()),color,2, 8, 0);

    ui->label->installEventFilter(this);
    ui->label->setPixmap(QPixmap::fromImage(QimgOriginalInput));
    ui->label_2->setPixmap(QPixmap::fromImage(QimgProcessedInput));
}

/*=============================================================================
 | Function used to draw the lines between points as to make a path for both
 | the actual position of the object and the predicted
 *===========================================================================*/
void MainWindow::drawActualAndPredictedPaths(){
    for(int i=0; i<listOfPoints.size()-1; i++)
        line(originalInput, Point(listOfPoints.at(i).x(), listOfPoints.at(i).y()), Point(listOfPoints.at(i+1).x(), listOfPoints.at(i+1).y()), Scalar(90,120,255),3);

    if(ui->radioButton->isChecked())
        line(originalInput,Point(listOfPoints.at(9).x(),listOfPoints.at(9).y()),Point(averaPredictionResults.at(0).x(),averaPredictionResults.at(0).y()), Scalar(205,255,255),3);


    if(ui->radioButton_3->isChecked()){
        if(counterForKalmanFilterOnly>10){
            for(int i=0; i<kalmanFilterResults.size()-1; i++)
                line(originalInput,Point(kalmanFilterResults.at(i).x(),kalmanFilterResults.at(i).y()),Point(kalmanFilterResults.at(i+1).x(),kalmanFilterResults.at(i+1).y()), Scalar(205,255,255),3);
        }
    }

    if(ui->radioButton_2->isChecked())
        line(originalInput,Point(listOfPoints.at(9).x(),listOfPoints.at(9).y()),Point(weightedPredictionResults.at(0).x(),weightedPredictionResults.at(0).y()), Scalar(205,255,255),3);
}

/*=============================================================================
 | Function used to calcualted the accuracy of the prediction and to plot the
 | real-time graph
 *===========================================================================*/
void MainWindow::calculateAccuracyAndPlotGraph(float centerX, float centerY){
    float percentageDiffX = 100-((abs(previousXPrediction-centerX)/centerX)*100);
    float percentageDiffY = 100-(abs(previousYPrediction-centerY)/centerY)*100;

    double absolutePercentage = (percentageDiffX+percentageDiffY)/2;

    ui->lcdNumber_4->display(absolutePercentage);

    if(counterUsedForPlot>10){
        QVector<double> temp1;
        QVector<double> temp2;

        for(int i=1; i<xPlotValues.size(); i++){
            temp1.append(xPlotValues.at(i));
            temp2.append(yPlotValues.at(i));
        }

        xPlotValues = temp1;
        yPlotValues = temp2;
    }

    xPlotValues.append((double) counterUsedForPlot);
    yPlotValues.append(absolutePercentage);

    ui->widget->addGraph();
    ui->widget->graph(0)->setData(xPlotValues, yPlotValues);

    ui->widget->xAxis->setRange(counterUsedForPlot-10,counterUsedForPlot);
    ui->widget->yAxis->setRange(0,105);
    ui->widget->replot();
}


void MainWindow::pauseResumeButtonLogic() {
    if(timerControl->isActive() == true) {
        timerControl->stop();
        ui->pauseResumeButton->setText(" Resume ");
    } else {
        timerControl->start(20);
        ui->pauseResumeButton->setText(" Pause ");
    }
}

void MainWindow::displayGraphButton(){

    if(displayGraphBool==true){
        displayGraphBool=false;
        counterUsedForPlot=0;
        ui->enableDisableGraphBtn->setText("Enable Graph");
    }
    else{
        displayGraphBool=true;
        counterUsedForPlot=0;
        ui->enableDisableGraphBtn->setText("Disable Graph");
    }
}

void MainWindow::removeSelectionLogic(){

    point1.setX(0);
    point1.setY(0);
    point2.setX(0);
    point2.setY(0);

    codeExecuted = false;
}


/*=============================================================================
 | EventFilter used to read the mousebuttons and positions to ensure that only
 | mouse events were allowed inside the label (PixMap)
 *===========================================================================*/
bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (qobject_cast<QLabel*>(obj)==ui->label && event->type() == QEvent::MouseButtonPress)
    {
        point2.setX(NULL);
        point2.setY(NULL);
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        codeExecuted = false;

        point1 = mouseEvent->pos();

        mousePressed=true;
    }

    if (qobject_cast<QLabel*>(obj)==ui->label && event->type() == QEvent::MouseButtonRelease)
    {
        clickCount = -1;
        mousePressed=false;

    }

    if (qobject_cast<QLabel*>(obj)==ui->label && event->type() == QEvent::MouseMove && mousePressed==true){

        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);

        if(mouseEvent->pos().x()>ui->label->size().width()){
            point2.setX(ui->label->size().width()-1);
        }

        else if(mouseEvent->pos().x()<0)
            point2.setX(1);

        else if(mouseEvent->pos().y()>ui->label->size().height())
            point2.setY(ui->label->size().height()-1);

        else if(mouseEvent->pos().y()<0)
            point2.setY(1);

        else
            point2 = mouseEvent->pos();
    }

    return false;
}

void MainWindow::setValuesAccordingToButton(){
    ui->spinBox->setValue(160);
    ui->spinBox_2->setValue(255);
    ui->spinBox_3->setValue(150);
}

void MainWindow::setValuesForBlue(){
    ui->spinBox->setValue(240);
    ui->spinBox_2->setValue(100);
    ui->spinBox_3->setValue(100);
}

void MainWindow::setValuesForRed(){
    ui->spinBox->setValue(0);
    ui->spinBox_2->setValue(100);
    ui->spinBox_3->setValue(100);
}

MainWindow::~MainWindow()
{
    delete ui;
}
