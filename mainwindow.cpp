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
#include "roi.h"
using namespace cv;
/** Global variables */
VideoCapture m_cap(0);
cv::String face_cascade_name = "haarcascade_frontalface_alt2.xml";
cv::String eyes_cascade_name = "haarcascade_eye.xml";
cv::CascadeClassifier face_cascade;
cv::CascadeClassifier eyes_cascade;
VideoFaceDetector detector(face_cascade_name,m_cap);
roi skin_roi;

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
    graphInit();

}

void MainWindow::updateGUI(){

    detector>>frame;

    cv::rectangle(frame, detector.face(), cv::Scalar(255, 0, 0));
    cv::circle(frame, detector.facePosition(), 30, cv::Scalar(0, 255, 0));

    if(detector.face().area()!=0){
       skin_roi.setRoiMat(detector.ROIframe(frame));
    }

    if(!skin_roi.getRoiMat().empty()){
        skin_roi.update();
        graphUpdate();
        skin_roi.increaseIteration();
        skin_roi.normaliseRGB();
        skin_roi.takeFFT();
        //qDebug()<<skin_roi.getBlueRoi();
    }

    ui->webcam_label->setPixmap(convertOpenCVMatToQtQPixmap(frame));
    ui->skinLabel->setPixmap(convertOpenCVMatToQtQPixmap2(skin_roi.getGreenRoi()));
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

    ui->chart_FFT->xAxis->setLabel("frame");
    ui->chart_FFT->yAxis->setLabel("intensity");
    ui->chart_FFT->legend->setVisible(true);
    ui->chart_FFT->setStyleSheet("background:hsva(255,255,255,0%);");
    ui->chart_FFT->setBackground(QBrush(Qt::NoBrush));
    ui->chart_FFT->yAxis->setVisible(false);
    ui->chart_FFT->xAxis->setVisible(false);

    ui->chart_FFT->addGraph();
    ui->chart_FFT->graph(0)->setName("blue");
    ui->chart_FFT->graph(0)->setPen(QPen(QColor(0,0,255)));

    ui->chart_FFT->addGraph();
    ui->chart_FFT->graph(1)->setName("green");
    ui->chart_FFT->graph(1)->setPen(QPen(QColor(0,255,0)));

    ui->chart_FFT->addGraph();
    ui->chart_FFT->graph(2)->setName("red");
    ui->chart_FFT->graph(2)->setPen(QPen(QColor(255,0,0)));

}

void MainWindow::graphUpdate(void){

    if(skin_roi.getIteratorVals().size()!=0){
        int x_min = skin_roi.getIteratorVals()[0];
        int x_max = skin_roi.getIteratorVals()[skin_roi.getIteratorVals().size()-1];
        ui->chart_FFT->xAxis->setRange(x_min,x_max);
    }

    ui->chart_FFT->yAxis->setRange(0,255);

    ui->chart_FFT->graph(0)->setData(skin_roi.getIteratorVals(),skin_roi.getBlueVals());
    ui->chart_FFT->graph(1)->setData(skin_roi.getIteratorVals(),skin_roi.getGreenVals());
    ui->chart_FFT->graph(2)->setData(skin_roi.getIteratorVals(),skin_roi.getRedVals());

    ui->chart_FFT->replot();
}

void MainWindow::takeFFT(QVector<double> input_vals , cv::Mat &output_vector ){
    cv::Mat input_vector;
    for(int i = m_xrange1; m_xrange2;i++){
        input_vector.push_back( input_vals[i]);
    }
    cv::dft(input_vector,output_vector);

}

void MainWindow::on_saveDataButton_clicked()
{
    //QFileDialog dialog(this);
    //dialog.setFileMode(QFileDialog::AnyFile);
    QString csv_file;
    csv_file= QFileDialog::getSaveFileName(this,tr("new csv"),"C:/Users/saul/Documents/MSc_Thesis/");
    QFile data (csv_file);
    if(data.open(QFile::WriteOnly|QFile::Truncate)){
        QTextStream output(&data);
        QVector<double> vector;
        vector = skin_roi.getRedVals();

        for(size_t i=0; i<vector.size();i++ ){
            output << vector[i]<<", ";
        }
    }
}
