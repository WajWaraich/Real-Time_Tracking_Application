/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_6;
    QVBoxLayout *verticalLayout;
    QLabel *label_5;
    QLabel *label_4;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_4;
    QSpinBox *spinBox;
    QSlider *vmin;
    QLCDNumber *lcdNumber;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QSpinBox *spinBox_2;
    QSlider *vmax;
    QLCDNumber *lcdNumber_2;
    QSpinBox *spinBox_3;
    QSlider *smin;
    QLCDNumber *lcdNumber_3;
    QCustomPlot *widget;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QLCDNumber *lcdNumber_4;
    QPushButton *enableDisableGraphBtn;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButton_2;
    QPushButton *pauseResumeButton;
    QPlainTextEdit *plainTextEdit;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1654, 784);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_6 = new QGridLayout(centralWidget);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setAutoFillBackground(true);

        verticalLayout->addWidget(label_5);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setAutoFillBackground(true);

        verticalLayout->addWidget(label_4);


        gridLayout_6->addLayout(verticalLayout, 0, 6, 1, 1);

        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        radioButton = new QRadioButton(groupBox_2);
        radioButton->setObjectName(QStringLiteral("radioButton"));

        gridLayout_2->addWidget(radioButton, 0, 0, 1, 1);

        radioButton_2 = new QRadioButton(groupBox_2);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));

        gridLayout_2->addWidget(radioButton_2, 1, 0, 1, 1);

        radioButton_3 = new QRadioButton(groupBox_2);
        radioButton_3->setObjectName(QStringLiteral("radioButton_3"));

        gridLayout_2->addWidget(radioButton_3, 2, 0, 1, 1);


        gridLayout_6->addWidget(groupBox_2, 3, 2, 1, 2);

        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        gridLayout_4 = new QGridLayout(groupBox_3);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        spinBox = new QSpinBox(groupBox_3);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setMaximum(256);

        gridLayout_4->addWidget(spinBox, 0, 0, 1, 1);

        vmin = new QSlider(groupBox_3);
        vmin->setObjectName(QStringLiteral("vmin"));
        vmin->setMaximum(256);
        vmin->setOrientation(Qt::Horizontal);

        gridLayout_4->addWidget(vmin, 0, 1, 1, 1);

        lcdNumber = new QLCDNumber(groupBox_3);
        lcdNumber->setObjectName(QStringLiteral("lcdNumber"));

        gridLayout_4->addWidget(lcdNumber, 0, 2, 1, 1);

        groupBox_4 = new QGroupBox(groupBox_3);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        gridLayout_3 = new QGridLayout(groupBox_4);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer, 0, 0, 1, 1);

        pushButton = new QPushButton(groupBox_4);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout_3->addWidget(pushButton, 0, 1, 1, 1);

        pushButton_3 = new QPushButton(groupBox_4);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        gridLayout_3->addWidget(pushButton_3, 1, 1, 1, 1);

        pushButton_4 = new QPushButton(groupBox_4);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        gridLayout_3->addWidget(pushButton_4, 2, 1, 1, 1);


        gridLayout_4->addWidget(groupBox_4, 0, 3, 3, 1);

        spinBox_2 = new QSpinBox(groupBox_3);
        spinBox_2->setObjectName(QStringLiteral("spinBox_2"));
        spinBox_2->setMaximum(256);

        gridLayout_4->addWidget(spinBox_2, 1, 0, 1, 1);

        vmax = new QSlider(groupBox_3);
        vmax->setObjectName(QStringLiteral("vmax"));
        vmax->setMaximum(256);
        vmax->setOrientation(Qt::Horizontal);

        gridLayout_4->addWidget(vmax, 1, 1, 1, 1);

        lcdNumber_2 = new QLCDNumber(groupBox_3);
        lcdNumber_2->setObjectName(QStringLiteral("lcdNumber_2"));

        gridLayout_4->addWidget(lcdNumber_2, 1, 2, 1, 1);

        spinBox_3 = new QSpinBox(groupBox_3);
        spinBox_3->setObjectName(QStringLiteral("spinBox_3"));
        spinBox_3->setMaximum(256);

        gridLayout_4->addWidget(spinBox_3, 2, 0, 1, 1);

        smin = new QSlider(groupBox_3);
        smin->setObjectName(QStringLiteral("smin"));
        smin->setMaximum(256);
        smin->setOrientation(Qt::Horizontal);

        gridLayout_4->addWidget(smin, 2, 1, 1, 1);

        lcdNumber_3 = new QLCDNumber(groupBox_3);
        lcdNumber_3->setObjectName(QStringLiteral("lcdNumber_3"));

        gridLayout_4->addWidget(lcdNumber_3, 2, 2, 1, 1);


        gridLayout_6->addWidget(groupBox_3, 2, 0, 2, 2);

        widget = new QCustomPlot(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        groupBox_2->raise();

        gridLayout_6->addWidget(widget, 1, 5, 3, 2);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 0, 0, 1, 1);

        lcdNumber_4 = new QLCDNumber(groupBox);
        lcdNumber_4->setObjectName(QStringLiteral("lcdNumber_4"));

        gridLayout->addWidget(lcdNumber_4, 0, 1, 1, 1);

        enableDisableGraphBtn = new QPushButton(groupBox);
        enableDisableGraphBtn->setObjectName(QStringLiteral("enableDisableGraphBtn"));

        gridLayout->addWidget(enableDisableGraphBtn, 1, 0, 1, 2);


        gridLayout_6->addWidget(groupBox, 3, 4, 1, 1);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setMouseTracking(true);
        label->setAutoFillBackground(true);
        label->setScaledContents(false);

        gridLayout_6->addWidget(label, 0, 0, 1, 3);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMouseTracking(false);
        label_2->setAutoFillBackground(true);
        label_2->setScaledContents(false);

        gridLayout_6->addWidget(label_2, 0, 3, 1, 3);

        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        gridLayout_6->addWidget(pushButton_2, 1, 1, 1, 1);

        pauseResumeButton = new QPushButton(centralWidget);
        pauseResumeButton->setObjectName(QStringLiteral("pauseResumeButton"));

        gridLayout_6->addWidget(pauseResumeButton, 1, 0, 1, 1);

        plainTextEdit = new QPlainTextEdit(centralWidget);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));
        plainTextEdit->setReadOnly(true);

        gridLayout_6->addWidget(plainTextEdit, 1, 2, 2, 3);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1654, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);
        QObject::connect(vmin, SIGNAL(valueChanged(int)), lcdNumber, SLOT(display(int)));
        QObject::connect(vmax, SIGNAL(valueChanged(int)), lcdNumber_2, SLOT(display(int)));
        QObject::connect(smin, SIGNAL(valueChanged(int)), lcdNumber_3, SLOT(display(int)));
        QObject::connect(spinBox, SIGNAL(valueChanged(int)), vmin, SLOT(setValue(int)));
        QObject::connect(spinBox_2, SIGNAL(valueChanged(int)), vmax, SLOT(setValue(int)));
        QObject::connect(spinBox_3, SIGNAL(valueChanged(int)), smin, SLOT(setValue(int)));
        QObject::connect(vmin, SIGNAL(valueChanged(int)), spinBox, SLOT(setValue(int)));
        QObject::connect(vmax, SIGNAL(valueChanged(int)), spinBox_2, SLOT(setValue(int)));
        QObject::connect(smin, SIGNAL(valueChanged(int)), spinBox_3, SLOT(setValue(int)));
        QObject::connect(pushButton, SIGNAL(clicked()), MainWindow, SLOT(setValuesAccordingToButton()));
        QObject::connect(pushButton_2, SIGNAL(pressed()), MainWindow, SLOT(removeSelectionLogic()));
        QObject::connect(enableDisableGraphBtn, SIGNAL(pressed()), MainWindow, SLOT(displayGraphButton()));
        QObject::connect(pauseResumeButton, SIGNAL(pressed()), MainWindow, SLOT(pauseResumeButtonLogic()));
        QObject::connect(pushButton_3, SIGNAL(pressed()), MainWindow, SLOT(setValuesForBlue()));
        QObject::connect(pushButton_4, SIGNAL(pressed()), MainWindow, SLOT(setValuesForRed()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        label_5->setText(QString());
        label_4->setText(QString());
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Prediction options", 0));
        radioButton->setText(QApplication::translate("MainWindow", "Average Prediction", 0));
        radioButton_2->setText(QApplication::translate("MainWindow", "Weighted Average Prediction", 0));
        radioButton_3->setText(QApplication::translate("MainWindow", "Kalman Filter Prediction", 0));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Thresholding using HSV colour-space", 0));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "                            Presets", 0));
        pushButton->setText(QApplication::translate("MainWindow", "Red tracking", 0));
        pushButton_3->setText(QApplication::translate("MainWindow", "Blue tracking", 0));
        pushButton_4->setText(QApplication::translate("MainWindow", "Green tracking", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Graph options", 0));
        label_3->setText(QApplication::translate("MainWindow", "Accuracy", 0));
        enableDisableGraphBtn->setText(QApplication::translate("MainWindow", "Enable graph", 0));
        label->setText(QString());
        label_2->setText(QString());
        pushButton_2->setText(QApplication::translate("MainWindow", "Remove selection", 0));
        pauseResumeButton->setText(QApplication::translate("MainWindow", "Pause", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
