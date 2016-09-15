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
//QString csv_file;
//csv_file= QFileDialog::getSaveFileName(this,tr("new csv"),"C:/Users/saul/Documents/MSc_Thesis/");
//QFile data (csv_file);
//if(data.open(QFile::WriteOnly|QFile::Truncate)){
//    QTextStream output(&data);

/** Global variables */
int g_play_flag;
int g_video=1;
std::vector<double> g_times;
int g_time_i;
double g_frame_count=0;
double g_current_frame=1;
QString g_csv_file = "C:/Users/saul/Documents/MSc_Thesis/results/vid2teststatic1.csv";
QFile g_data(g_csv_file);
QTextStream g_output_file(&g_data);

QString g_csv_file2 = "C:/Users/saul/Documents/MSc_Thesis/results/vid2testalldatastatic1.csv";
QFile g_data2(g_csv_file2);
QTextStream g_output_file2(&g_data2);

double g_tick_frequency;

std::vector<double>g_sinwave;
std::vector<double> g_fft,g_fft_test;
VideoCapture m_cap(0);
cv::String face_cascade_name = "haarcascade_frontalface_alt2.xml";
cv::String eyes_cascade_name = "haarcascade_eye.xml";
cv::CascadeClassifier face_cascade;
cv::CascadeClassifier eyes_cascade;
VideoFaceDetector detector(face_cascade_name,m_cap);
roi skin_roi;
roi static_roi;
codetimer code_timer;
int static_flag=0;
std::string window_name = "Capture - Face detection";
cv::RNG rng(12345);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    g_data.open(QFile::WriteOnly|QFile::Truncate);
    g_data2.open(QFile::WriteOnly|QFile::Truncate);

    g_times.push_back(0);
    g_time_i = 1;


    //    QString csv_file;
    //    csv_file= QFileDialog::getSaveFileName(this,tr("new csv"),"C:/Users/saul/Documents/MSc_Thesis/");
    //    QFile data (csv_file);
    //    if(data.open(QFile::WriteOnly|QFile::Truncate)){
    //        QTextStream output(&data);
    //    }


    if(!m_cap.open(0)){
        qDebug()<<"webcam no open";
    }
    //m_cap.set(CV_CAP_PROP_FPS,15);

    if( !face_cascade.load( face_cascade_name ) ){ qDebug()<<"can´t find face_cascade xml"; }
    if( !eyes_cascade.load( eyes_cascade_name ) ){ qDebug()<<"can´t find eye_cascade xml"; }

    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(updateGUI()));
    timer->start();
    graphInit();

}

void MainWindow::updateGUI(){

    if(g_play_flag==1){
        qDebug()<<g_frame_count<<", "<<g_current_frame;
        if((g_frame_count-5)!=g_current_frame){


            if(m_cap.isOpened()){

                g_frame_count=m_cap.get(CV_CAP_PROP_FRAME_COUNT );
                g_current_frame = m_cap.get(CV_CAP_PROP_POS_FRAMES);
                int time = m_cap.get(CV_CAP_PROP_POS_MSEC);
                ui->lcd_time->display(time);
                int fps = m_cap.get(CV_CAP_PROP_FPS);
                g_tick_frequency = cv::getTickFrequency();
                //ui->tick_freq_lcd->display(g_tick_frequency);

                detector>>frame;

                cv::rectangle(frame, detector.face(), cv::Scalar(255, 0, 0));
                cv::rectangle(frame, static_roi.getRect(), cv::Scalar(255, 0, 0));

                cv::circle(frame, detector.facePosition(), 30, cv::Scalar(0, 255, 0));
                if(!frame.empty()){
                if(detector.face().area()!=0){


                    if(static_flag==0){
                        static_roi.setFacePosition(detector.facePosition());
                        static_roi.setFaceWidth(detector.face().width);
                        static_flag=1;
                    }
                    skin_roi.setRoiMat(detector.ROIframe(frame));
                    static_roi.setStaticRoi(frame);

                }
    }

                if(!skin_roi.getRoiMat().empty()){

                    code_timer.startTimer();
                    skin_roi.update();
                    static_roi.update();

                    graphUpdate();
                    skin_roi.increaseIteration();
                    static_roi.increaseIteration();
                    cv::Mat ica_out,weights,ica_out_static, weights_static;

                    //only take ica every nth frame to speed up
                    int iteration =  skin_roi.getIteration();
                    int frame_rate = FRAME_SIZE;
                    qDebug()<<iteration;
                    if(iteration%frame_rate==0){
                        g_times.push_back(double(time));
                        code_timer.endTimer();
                        skin_roi.setCodeTimer(code_timer.getTime());
                        skin_roi.normaliseRGB();
                        static_roi.normaliseRGB();

                        //            cv::Mat ica_matrix = skin_roi.createIcaMatrix(
                        //                        skin_roi.getRedNorm(),skin_roi.getGreenNorm(),skin_roi.getBlueNorm());
                        //            cv::Mat ica_matrix_static = static_roi.createIcaMatrix(static_roi.getRedNorm(),
                        //                                                                   static_roi.getGreenNorm(),
                        //                                                                   static_roi.getBlueNorm());

                        //            skin_roi.setIcaMatrix(ica_matrix);
                        //            static_roi.setIcaMatrix(ica_matrix_static);

                        //            skin_roi.setRemeanMatrix(skin_roi.getIcaMatrix());
                        //            static_roi.setRemeanMatrix(static_roi.getIcaMatrix());
                        //            cv::Mat rm;
                        //            cv::Mat rm_static;
                        //            rm = skin_roi.getRemeanMatrix();
                        //            rm_static=static_roi.getRemeanMatrix();

                        //printMatrix(rm);
                        //whiten fucntion dosent work
                        //skin_roi.setWhitenMatrix(rm);

                        //skin_roi.runIca(rm,ica_out,weights,rm.cols);
                        //static_roi.runIca(rm_static,ica_out_static,weights_static,rm_static.cols);
                        //printMatrix(ica_out);
                        //ica_out = ica_out.t();
                        //ica_out_static=ica_out_static.t();

                        // skin_roi.setIcaSignal(ica_out);
                        // static_roi.setIcaSignal(ica_out_static);

                        std::vector<double> greenfft = skin_roi.takeFFT(skin_roi.getGreenNorm());
                        std::vector<double> greenfft_static = static_roi.takeFFT(static_roi.getGreenNorm());
                        skin_roi.findMaxFft(greenfft);
                        static_roi.findMaxFft(greenfft_static);
                        double bpm1 = skin_roi.getBpm();
                        double bpm2 = static_roi.getBpm();
                        ui->lcd_tracked->display(skin_roi.getBpm());
                        ui->lcd_static->display(static_roi.getBpm());


                        g_sinwave = skin_roi.generateSinWave(100);
                        g_fft_test = skin_roi.takeFFT(g_sinwave);

                        QTextStream output(&g_data);
                        QTextStream output2(&g_data2);


                        output<<g_video<<","skin_roi.getBpm()<<","<<static_roi.getBpm()<<
                                ","<<m_cap.get(CV_CAP_PROP_POS_MSEC)<<endl;

                        std::vector<double> fft_green = skin_roi.getGreenFft();
                        //std::vector<double> ica_green_signal;
                        std::vector<double> raw_green = skin_roi.getGreenVals().toStdVector();

                        std::vector<double> fft_green_static = static_roi.getGreenFft();
                        //std::vector<double> ica_green_signal_static;
                        std::vector<double> raw_green_static = static_roi.getGreenVals().toStdVector();

                        //ica_out.row(1).copyTo(ica_green_signal);

                        //ica_out_static.row(1).copyTo(ica_green_signal_static);

                        //make a vector of frequency for the power distribution
                        std::vector<double> freq;
                        double framesize = FRAME_SIZE;
                        double frame_time = (g_times[g_time_i]-g_times[g_time_i-1])/1000;

                        //            for(double i =1;i<framesize/2;i++){
                        //                freq.push_back(i* 60/(frame_time));
                        //            }
                        //            //find max frequency i.e heart rate
                        //            double maxf=0;
                        //            double bufferf =0;
                        //            int pos=0;
                        //            for(int i =0;i<framesize/2;i++){
                        //               if((fft_green[i]>bufferf)&&(freq[i]>30)&&(freq[i]<90)){
                        //                  bufferf = fft_green[i];
                        //                   maxf = freq[i];
                        //                   pos=i;
                        //               }
                        //            }
                        //            double maxf2=0;
                        //            double bufferf2 =0;
                        //            int pos2=0;
                        //            for(int i =0;i<framesize/2;i++){
                        //               if((fft_green_static[i]>bufferf2)&&(freq[i]>30)&&(freq[i]<90)){
                        //                  bufferf2 = fft_green_static[i];
                        //                   maxf2 = freq[i];
                        //                   pos2=i;
                        //               }
                        //            }
                        //            output<<maxf<<","<<pos<<","<<time<<","<<maxf2<<","<<pos2<<endl;
                        //            g_time_i++;

                        //            for(int i=0; i<fft_green.size();i++){
                        //                output2<<raw_green[i]<<","<<","<<fft_green[i]<<","<<time<<","
                        //                      <<raw_green_static[i]<<","<<","
                        //                     <<fft_green_static[i]<<endl;
                        //            }


                        ui->tick_label->setText("done");
                        //            std::vector<double> fft1,fft2,fft3;
                        //ica_out = ica_out.t();
                        //           ica_out.row(0).copyTo(fft1);
                        //           ica_out.row(1).copyTo(fft2);
                        //           ica_out.row(2).copyTo(fft3);

                        //          g_fft=skin_roi.takeFFT(fft2);
                    }
                    //skin_roi.setIcaSignal(ica_out);
                    //skin_roi.setTestSignal(signalGenerate());
                    //skin_roi.takeFFT();

                    //qDebug()<<skin_roi.getBlueRoi();
                }

                ui->webcam_label->setPixmap(convertOpenCVMatToQtQPixmap(frame));
                ui->skinLabel->setPixmap(convertOpenCVMatToQtQPixmap2(skin_roi.getGreenRoi()));
            }
        }
        else{

            m_cap.release();
            string filename="C:/a/";
            filename+= std::to_string(g_video);
            filename+=".avi";

            m_cap = cv::VideoCapture(filename);
            g_frame_count=m_cap.get(CV_CAP_PROP_FRAME_COUNT );
            g_current_frame = m_cap.get(CV_CAP_PROP_POS_FRAMES);
            g_video++;

        }
    }
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
                                              tr("Open Image"), "C:/Users/saul/Documents/MSc_Thesis/hci-tagging-database_download_2016-07-22_11-16-38/Sessions/", tr("video Files (*.mpg *.avi *.mp4)"));
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
                line.append( QString::number(mat.at<double>(j,i)));

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

    ui->chart_FFT->addGraph();

    ui->chart_FFT->graph(3)->setName("static green");
    ui->chart_FFT->graph(3)->setPen(QPen(QColor(100,255,100)));

}

void MainWindow::graphUpdate(void){

    if(skin_roi.getIteratorVals().size()!=0){
        int x_min = skin_roi.getIteratorVals()[0];
        int x_max = skin_roi.getIteratorVals()[skin_roi.getIteratorVals().size()-1];
        ui->chart_FFT->xAxis->setRange(x_min,x_max);
    }

    ui->chart_FFT->yAxis->setRange(60,120);

    ui->chart_FFT->graph(0)->setData(skin_roi.getIteratorVals(),skin_roi.getBlueVals());
    ui->chart_FFT->graph(1)->setData(skin_roi.getIteratorVals(),skin_roi.getGreenVals());
    ui->chart_FFT->graph(2)->setData(skin_roi.getIteratorVals(),skin_roi.getRedVals());
    QVector<double> staticgreen = static_roi.getGreenVals();
    ui->chart_FFT->graph(3)->setData(skin_roi.getIteratorVals(),staticgreen);


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
        QVector<double> vector_red,vector_green, vector_blue ;
        vector_red = skin_roi.getRedVals();
        vector_green = skin_roi.getGreenVals();
        vector_blue = skin_roi.getBlueVals();
        std::vector<double> norm_red= skin_roi.getRedNorm();
        std::vector<double> matr1,matr2,matr3,icaout1,icaout2,icaout3;
        skin_roi.getIcaMatrix().row(0).copyTo(matr1);
        skin_roi.getIcaMatrix().row(1).copyTo(matr2);
        skin_roi.getIcaMatrix().row(2).copyTo(matr3);
        cv::Mat icamat = skin_roi.getIcaSignal();
        icaout1= icamat.row(0);
        icaout2= icamat.row(1);
        icaout3= icamat.row(2);
        std::vector<double> redfft = skin_roi.getRedFft();
        std::vector<double> greenfft = skin_roi.getGreenFft();

        std::vector<double> bluefft = skin_roi.getBlueFft();


        double maxfreq = skin_roi.findMax(greenfft);

        output<<"i,red, green, blue,red norm, green norm,blue norm, ica matrix row0,row1,row2,"
                "ica out row0, row1, row2,fft green,period,max freq"<<endl;
        for(size_t i=0; i<vector_red.size();i++ ){
            output << i<<","<<vector_red[i]<<","<<vector_green[i]<<","<<vector_blue[i]<<","
                   << norm_red[i]<<","<< skin_roi.getGreenNorm()[i]<<","<<skin_roi.getBlueNorm()[i]
                      <<","<<matr1[i]<<","
                     <<matr2[i]<<","<<matr3[i]<<","
                    <<icaout1[i]<<","<<icaout2[i]<<","<<icaout3[i]<<","<<greenfft[i]
                      <<","<<skin_roi.getCodeTimer()<<","<<maxfreq<<endl;
            //","<<g_sinwave[i]<<","<<g_fft_test[i]<<endl;
        }
    }
}

vector<double> MainWindow::signalGenerate(void){
    std::vector<double> signal;
    int flag=0;
    for (int i=0;i<450;i++){
        if(i%10==0){
            if(flag==0){
                flag =1;
            }
            else if(flag==1){
                flag=0;
            }
        }

        if(flag==1){
            signal.push_back(1);
        }
        else if(flag==0){
            signal.push_back(0);
        }
    }
    return signal;
}


void setTimer(void){

}

void MainWindow::on_playButton_clicked()
{
    if(g_play_flag==0){
        g_play_flag = 1;
    }
    else if (g_play_flag==1){
        g_play_flag=0;
    }
}
