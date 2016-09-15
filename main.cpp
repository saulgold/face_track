#include "mainwindow.h"
#include <QApplication>

double g_iteration =0;



int main(int argc, char *argv[])
{
    cv::Point g_face_position;
    int g_face_width;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
