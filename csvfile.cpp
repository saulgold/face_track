#include "csvfile.h"

csvfile::csvfile(QString filename)
{
    m_file_name = filename;


}
void csvfile::setFile(QString filename){
    m_file_name = filename;
}

QString csvfile::getFileName(){
    return m_file_name;
}




//QString csv_file;
//csv_file= QFileDialog::getSaveFileName(this,tr("new csv"),"C:/Users/saul/Documents/MSc_Thesis/");
//QFile data (csv_file);
//if(data.open(QFile::WriteOnly|QFile::Truncate)){
//    QTextStream output(&data);
