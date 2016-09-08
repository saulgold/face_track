#include "csvfile.h"

csvfile::csvfile(QString filename)
{
    m_file_name = filename;
    QFile data(m_file_name);

}

void csvfile::setFileName(QString fn){
    m_file_name = fn;
    QFile data(m_file_name);


}

void csvfile::sendToFile(QTextStream send){
    if(m_data.open(QFile::WriteOnly|QFile::Truncate)){
        QTextStream send2(&m_data);

    }
}
//QString csv_file;
//csv_file= QFileDialog::getSaveFileName(this,tr("new csv"),"C:/Users/saul/Documents/MSc_Thesis/");
//QFile data (csv_file);
//if(data.open(QFile::WriteOnly|QFile::Truncate)){
//    QTextStream output(&data);
