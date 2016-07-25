#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <video.hpp>
#include <stdio.h>
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/nonfree/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;
/** Global variables */
cv::String face_cascade_name = "haarcascade_frontalface_alt2.xml";
cv::String eyes_cascade_name = "haarcascade_eye.xml";
VideoCapture cap;

cv::CascadeClassifier face_cascade;
cv::CascadeClassifier eyes_cascade;
VideoCapture m_cap;


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

    //capture frame from default webcam
    m_cap>>m_frame_col;

    if(!m_frame_col.empty()){
        //-- 1. Load the cascades

        detectAndDisplay(m_frame_col);
        qframe = convertOpenCVMatToQtQImage(m_frame_col);
        QPixmap pix = QPixmap::fromImage(qframe);
        ui->webcam_label->setPixmap(pix);
    }
    else(qDebug()<<"frame empty");


}

MainWindow::~MainWindow()
{
    delete ui;
}
/** @function detectAndDisplay */
void MainWindow::detectAndDisplay( cv::Mat frame )
{
  std::vector<cv::Rect> faces;
  cv::Mat frame_gray;

  cv::cvtColor( frame, frame_gray, CV_BGR2GRAY );
  cv::equalizeHist( frame_gray, frame_gray );

  //-- Detect faces

  face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, cv::Size(30, 30) );

  for( size_t i = 0; i < faces.size(); i++ )
  {
    cv::Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
    cv::ellipse( frame, center, cv::Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, cv::Scalar( 255, 0, 255 ), 4, 8, 0 );

    cv::Mat faceROI = frame_gray( faces[i] );
    std::vector<cv::Rect> eyes;

//    -- In each face, detect eyes
    eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, cv::Size(30, 30) );

    for( size_t j = 0; j < eyes.size(); j++ )
     {
       cv::Point center( faces[i].x + eyes[j].x + eyes[j].width*0.5, faces[i].y + eyes[j].y + eyes[j].height*0.5 );
       int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
       cv::circle( frame, center, radius, cv::Scalar( 255, 0, 0 ), 4, 8, 0 );
     }
  }

}

QImage MainWindow::convertOpenCVMatToQtQImage(cv::Mat mat) {
    if(mat.channels() == 1) {                   // if grayscale image
        return QImage((uchar*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Indexed8);     // declare and return a QImage
    } else if(mat.channels() == 3) {            // if 3 channel color image
        cv::cvtColor(mat, mat, CV_BGR2RGB);     // invert BGR to RGB
        return QImage((uchar*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);       // declare and return a QImage
         qDebug() << "in convertOpenCVMatToQtQImage, image was not 1 channel or 3 channel, should never get here";
    }
    return QImage();        // return a blank QImage if the above did not work
}
