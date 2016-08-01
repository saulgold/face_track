#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <video.hpp>
#include <stdio.h>
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/nonfree/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "VideoFaceDetector.h"

using namespace cv;
/** Global variables */
VideoCapture m_cap(0);
cv::String face_cascade_name = "haarcascade_frontalface_alt2.xml";
cv::String eyes_cascade_name = "haarcascade_eye.xml";
cv::CascadeClassifier face_cascade;
cv::CascadeClassifier eyes_cascade;
VideoFaceDetector detector(face_cascade_name,m_cap);


std::string window_name = "Capture - Face detection";
cv::RNG rng(12345);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    if(!m_cap.open(0)){
        qDebug()<<"webcam no open";
    }
    if( !face_cascade.load( face_cascade_name ) ){ qDebug()<<"can´t find face_cascade xml"; }
    if( !eyes_cascade.load( eyes_cascade_name ) ){ qDebug()<<"can´t find eye_cascade xml"; }

    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(updateGUI()));
    timer->start();

}

void MainWindow::updateGUI(){


    detector>>frame;

    cv::rectangle(frame, detector.face(), cv::Scalar(255, 0, 0));
    cv::circle(frame, detector.facePosition(), 30, cv::Scalar(0, 255, 0));

    if(detector.face().area()!=0){
        detector.getROI(frame,m_skinFrame);
//        cv::Rect middleFaceRect = Rect(detector.facePosition().x-10,detector.facePosition().y-10,20,20);
//        m_skinFrame = cv::Mat(frame,middleFaceRect);
//        cv::rectangle(frame,middleFaceRect,cv::Scalar(0,0,255),1,8,0);
    }
    cv::Mat icaWeights;



    if(!m_skinFrame.empty()){
        cv::randu(icaWeights,Scalar(-1,-1,-1),Scalar(1,1,1));
        cv::cvtColor(m_skinFrame,m_skinFrame,CV_BGR2GRAY);
        m_skinFrame.convertTo(m_skinFrame,CV_64F);
        //ica->recursiveICA(m_skinFrame,icaWeights);
}

    ui->webcam_label->setPixmap(convertOpenCVMatToQtQPixmap(frame));
    ui->skinLabel->setPixmap(convertOpenCVMatToQtQPixmap2(m_skinFrame));



}

MainWindow::~MainWindow()
{
    delete ui;
}


QPixmap MainWindow::convertOpenCVMatToQtQPixmap(cv::Mat mat) {
    if(mat.channels() == 1) {                   // if grayscale image
        //cv::flip(mat,mat,1);
        QImage qFrame =  QImage((uchar*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Indexed8);     // declare and return a QImage
        return QPixmap::fromImage(qFrame);
    } else if(mat.channels() == 3) {            // if 3 channel color image
        //cv::flip(mat,mat,1);
        cv::cvtColor(mat, mat, CV_BGR2RGB);     // invert BGR to RGB
        QImage qFrame = QImage((uchar*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);       // declare and return a QImage
        return QPixmap::fromImage(qFrame);
        qDebug() << "in convertOpenCVMatToQtQImage, image was not 1 channel or 3 channel, should never get here";
    }
    return QPixmap();        // return a blank QImage if the above did not work
}
QPixmap MainWindow::convertOpenCVMatToQtQPixmap2(cv::Mat mat) {
    if(mat.channels() == 1) {                   // if grayscale image
        //cv::flip(mat,mat,1);
        QImage qFrame =  QImage((uchar*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Indexed8);     // declare and return a QImage
        return QPixmap::fromImage(qFrame);
    } else if(mat.channels() == 3) {            // if 3 channel color image
        //cv::flip(mat,mat,1);
       // cv::cvtColor(mat, mat, CV_BGR2RGB);     // invert BGR to RGB
        QImage qFrame = QImage((uchar*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);       // declare and return a QImage
        return QPixmap::fromImage(qFrame);
        qDebug() << "in convertOpenCVMatToQtQImage, image was not 1 channel or 3 channel, should never get here";
    }
    return QPixmap();        // return a blank QImage if the above did not work
}

void MainWindow::on_selectFileButton_clicked()
{
    m_filename = QFileDialog::getOpenFileName(this,
        tr("Open Image"), "C:/Users/saul/Documents/MSc_Thesis/hci-tagging-database_download_2016-07-22_11-16-38/Sessions/", tr("video Files (*.mpg *.avi)"));
    m_cap = cv::VideoCapture(m_filename.toStdString());

}


