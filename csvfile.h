#ifndef CSVFILE_H
#define CSVFILE_H
#include "mainwindow.h"
#include<QString>

class csvfile
{
public:
    csvfile(QString filename);
    ~csvfile();
    void setFileName(QString fn);
    void sendToFile(QTextStream send);
private:
    QString m_file_name;
    QFile m_data;
};

#endif CSVFILE_H
//QString csv_file;
//csv_file= QFileDialog::getSaveFileName(this,tr("new csv"),"C:/Users/saul/Documents/MSc_Thesis/");
//QFile data (csv_file);
//if(data.open(QFile::WriteOnly|QFile::Truncate)){
//    QTextStream output(&data);
