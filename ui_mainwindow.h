/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGraphicsView *graphicsView;
    QGraphicsView *nextView;
    QGraphicsView *holdView;
    QLabel *label;
    QLabel *label_2;
    QPushButton *startButton;
    QPushButton *stopButton;
    QPushButton *closeButton;
    QLabel *label_3;
    QLCDNumber *score;
    QLabel *tetrisCount;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(700, 675);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(10, 10, 300, 600));
        nextView = new QGraphicsView(centralWidget);
        nextView->setObjectName(QString::fromUtf8("nextView"));
        nextView->setGeometry(QRect(320, 50, 180, 120));
        holdView = new QGraphicsView(centralWidget);
        holdView->setObjectName(QString::fromUtf8("holdView"));
        holdView->setGeometry(QRect(320, 200, 180, 120));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(320, 30, 81, 21));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(320, 180, 81, 21));
        startButton = new QPushButton(centralWidget);
        startButton->setObjectName(QString::fromUtf8("startButton"));
        startButton->setGeometry(QRect(320, 350, 181, 41));
        stopButton = new QPushButton(centralWidget);
        stopButton->setObjectName(QString::fromUtf8("stopButton"));
        stopButton->setGeometry(QRect(320, 400, 181, 41));
        closeButton = new QPushButton(centralWidget);
        closeButton->setObjectName(QString::fromUtf8("closeButton"));
        closeButton->setGeometry(QRect(320, 570, 181, 41));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(320, 460, 59, 16));
        score = new QLCDNumber(centralWidget);
        score->setObjectName(QString::fromUtf8("score"));
        score->setGeometry(QRect(320, 480, 181, 31));
        tetrisCount = new QLabel(centralWidget);
        tetrisCount->setObjectName(QString::fromUtf8("tetrisCount"));
        tetrisCount->setGeometry(QRect(320, 520, 181, 16));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 700, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);
        QObject::connect(closeButton, SIGNAL(clicked()), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QApplication::translate("MainWindow", "NEXT:", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "ON HOLD:", nullptr));
        startButton->setText(QApplication::translate("MainWindow", "START", nullptr));
        stopButton->setText(QApplication::translate("MainWindow", "STOP", nullptr));
        closeButton->setText(QApplication::translate("MainWindow", "CLOSE", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "SCORE:", nullptr));
        tetrisCount->setText(QApplication::translate("MainWindow", "Tetris count: 0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
