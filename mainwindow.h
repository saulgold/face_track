#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <stdio.h>
#include <opencv2/core/core.hpp>
#include<opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/video.hpp>
#include "qdebug.h"
#include <QImage>
#include <QtCore>
#include<iostream>
#include<vector>
#include<algorithm>
//#include"vidcap.h"
#include "opencv2/opencv.hpp"
#include <vector>
#include <stdio.h>
#include<stdlib.h>
 #include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

#include <opencv2/imgproc/imgproc_c.h>
#include "opencv2/imgproc.hpp"
#include <opencv2/features2d/features2d.hpp>
#include "ml.h"
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <opencv2/video/background_segm.hpp>
#include <QTime>
#include <QFileDialog>
#include <recursive_ica.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void updateGUI();

    void on_selectFileButton_clicked();

private:
    Ui::MainWindow *ui;

    cv::Mat m_frame_col,frame;
    QTimer *timer;
    QImage qframe;
    QString m_filename;
    //cv::VideoCapture m_cap;

    /** Function Headers */
    void detectAndDisplay( cv::Mat inframe );
    QPixmap convertOpenCVMatToQtQPixmap(cv::Mat mat);
    //to deal with the ROI
    QPixmap convertOpenCVMatToQtQPixmap2(cv::Mat mat);
    cv::Mat m_skinFrame;
    void printMatrix(cv::Mat mat);
    void recursiveICA2(cv::Mat datargb, cv::Mat & weights);

};

#endif // MAINWINDOW_H
