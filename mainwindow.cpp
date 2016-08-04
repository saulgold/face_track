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
#include "qcustomplot.h"


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
    if(!m_cap.open(1)){
        qDebug()<<"webcam no open";
    }
    if( !face_cascade.load( face_cascade_name ) ){ qDebug()<<"can´t find face_cascade xml"; }
    if( !eyes_cascade.load( eyes_cascade_name ) ){ qDebug()<<"can´t find eye_cascade xml"; }

    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(updateGUI()));
    timer->start();
    graphInit();

}

void MainWindow::updateGUI(){


    detector>>frame;

    cv::rectangle(frame, detector.face(), cv::Scalar(255, 0, 0));
    cv::circle(frame, detector.facePosition(), 30, cv::Scalar(0, 255, 0));

    if(detector.face().area()!=0){
       m_skinFrame = detector.ROIframe(frame);
    }
    cv::Mat icaWeights;

cv::Mat blue, green, red;
    if(!m_skinFrame.empty()){

        blue = m_skinFrame - cv::Scalar(0,255,255);
        green = m_skinFrame - cv::Scalar(255,0,255);
        red = m_skinFrame - cv::Scalar(255,255,0);

        m_blue_average = cv::mean(blue);
        m_green_average = cv::mean(green);
        m_red_average = cv::mean(red);

        graphUpdate();



}

    ui->webcam_label->setPixmap(convertOpenCVMatToQtQPixmap(frame));
    ui->skinLabel->setPixmap(convertOpenCVMatToQtQPixmap2(green));



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
            if(mat.channels() ==3){
            line.append( QString::number(mat.at<Vec3b>(j,i)[0]));
           line.append(QString(","));
           line.append( QString::number (mat.at<Vec3b>(j,i)[1]));
          line.append(QString(","));
          line.append( QString::number (mat.at<Vec3b>(j,i)[2]));
         line.append(QString("    "));
            }
            else if(mat.channels() ==1){
                line.append( QString::number(mat.at<uchar>(j,i)));

            }
            else{qDebug()<<"no channels in matrix";}
        }
        qDebug()<< line;
        line.clear();
    }
}

void MainWindow::graphInit(void){
    ui->chart1->addGraph();
    ui->chart1->graph(0)->setName("blue");
    ui->chart1->graph(0)->setPen(QPen(QColor(0,0,255)));

    ui->chart1->addGraph();
    ui->chart1->graph(1)->setName("green");
    ui->chart1->graph(1)->setPen(QPen(QColor(0,255,0)));

    ui->chart1->addGraph();
    ui->chart1->graph(2)->setName("red");
    ui->chart1->graph(2)->setPen(QPen(QColor(255,0,0)));

    ui->chart1->xAxis->setLabel("frame");
    ui->chart1->yAxis->setLabel("intensity");
    ui->chart1->xAxis->setAutoTickStep(true);
    ui->chart1->yAxis->setAutoTickStep(true);
    ui->chart1->legend->setVisible(true);
    ui->chart1->setStyleSheet("background:hsva(255,255,255,0%);");
    ui->chart1->setBackground(QBrush(Qt::NoBrush));
}

void MainWindow::graphUpdate(void){
    if(m_iteration<450){
        m_xrange1 =0;
        m_xrange2=450;
    }else if(m_iteration>=450){
        m_xrange1 = m_iteration - 450;
        m_xrange2 = m_iteration;
    }
    m_yrange1 = (m_blue_average[0] + m_green_average[1]+m_red_average[2])/3 - 100;
    m_yrange2 = (m_blue_average[0] + m_green_average[1]+m_red_average[2])/3 + 100;
    ui->chart1->yAxis->setRange(m_yrange1,m_yrange2);
    ui->chart1->xAxis->setRange(m_xrange1,m_xrange2);
    ui->chart1->yAxis->setVisible(false);
    ui->chart1->xAxis->setVisible(false);
    m_blue_vals.append(m_blue_average[0]);
    m_green_vals.append(m_green_average[1]);
    m_red_vals.append(m_red_average[2]);

    m_frame_iteration.append(m_iteration);
    m_iteration++;
    ui->chart1->graph(0)->setData(m_frame_iteration,m_blue_vals);
    ui->chart1->graph(1)->setData(m_frame_iteration,m_green_vals);
    ui->chart1->graph(2)->setData(m_frame_iteration,m_red_vals);

    ui->chart1->replot();
}
