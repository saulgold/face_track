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
cv::String face_cascade_name = "haarcascade_frontalface_alt2.xml";
cv::String eyes_cascade_name = "haarcascade_eye.xml";
VideoCapture cap;

cv::CascadeClassifier face_cascade;
cv::CascadeClassifier eyes_cascade;
VideoCapture m_cap(0);
VideoFaceDetector detector(face_cascade_name,m_cap);
RecursiveICA *ica=new RecursiveICA(0.995);

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
        cv::Rect middleFaceRect = Rect(detector.facePosition().x-10,detector.facePosition().y-10,20,20);
        m_skinFrame = cv::Mat(frame,middleFaceRect);
        cv::rectangle(frame,middleFaceRect,cv::Scalar(0,0,255),1,8,0);



    }
    //cv::Mat faceFrame = cv::Mat(frame,detector.face());
   // cv::cvtColor(faceFrame,faceFrame,CV_BGR2RGB);
    //m_skinFrame.convertTo(m_skinFrame,CV_64F);
    cv::Mat tframe;

    tframe=Mat::ones(3,3,CV_64F)*100;
    cv::Mat icaWeights;
    //icaWeights.create(m_skinFrame.cols, m_skinFrame.rows, CV_64F);
  // m_skinFrame.convertTo(m_skinFrame,CV_64FC1);


    //recursiveICA2(m_skinFrame,icaWeights);


    if(!m_skinFrame.empty()){
        cv::randu(icaWeights,Scalar(-1,-1,-1),Scalar(1,1,1));
        cv::cvtColor(m_skinFrame,m_skinFrame,CV_BGR2GRAY);
        //m_skinFrame.convertTo(m_skinFrame,CV_64F);
        ica->recursiveICA(m_skinFrame,icaWeights);

    //printMatrix(m_skinFrame.col(0));
    //printMatrix(icaWeights);
    //cv::Mat y = icaWeights * m_skinFrame.col(0);
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
void MainWindow::printMatrix(cv::Mat mat){
    QString line;
    for(int i=0; i<mat.cols;++i){
        for(int j=0;j<mat.rows;++j){

            line.append( QString::number(mat.at<Vec3b>(j,i)[0]));
           line.append(QString(","));
           line.append( QString::number (mat.at<Vec3b>(j,i)[1]));
          line.append(QString(","));
          line.append( QString::number (mat.at<Vec3b>(j,i)[2]));
         line.append(QString("    "));

        }
        qDebug()<< line;
        line.clear();
    }
}

void MainWindow::recursiveICA2(cv::Mat datargb, cv::Mat & weights)
{

 // getDataRows(datargb, dataRows);
  //getDataCols(datargb, dataCols);
  int lmdinit = 0.99;
  int dataRows = datargb.rows;
  int dataCols = datargb.cols;
  weights.create(dataRows, dataRows, CV_64F);
  cv::randu(weights, Scalar(-1), Scalar(1));

  cv::cvtColor(weights,weights,CV_GRAY2RGB);
  int iterate_num=0;
  datargb.convertTo(datargb,CV_64F);

  for (int i=0;i<dataCols;i++)
    {
  iterate_num++;
  cv::transpose(weights,weights);

  cv::Mat y = weights*datargb.col(i);


  cv::Mat tanh1, tanh2;
  exp(y,tanh1);
  exp(-1*y,tanh2);
  cv::Mat nonlin=(tanh1-tanh2)/(tanh1+tanh2);

  cv::Mat gn=weights.t() * nonlin;
  double lmd=lmdinit/pow((double)iterate_num, 0.7);
  weights=weights+(lmd/(1-lmd))*(weights-((y*gn.t())/(1+lmd*(nonlin.t()*y-1))));

  y.release();
  tanh1.release();
  tanh2.release();
  nonlin.release();
  gn.release();
    }
}
