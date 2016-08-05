#include "roi.h"

roi::roi()
{

}

roi::~roi(){

}

void roi::setRoiMat(Mat roiMat){
    roi_mat = roiMat;
}

cv::Mat roi::getRoiMat()
{
    return roi_mat;
}
cv::Mat roi::getBlueRoi()
{
    cv::Mat blue_roi = roi_mat - cv::Scalar(0,255,255);
    return blue_roi;

}
cv::Mat roi::getGreenRoi()
{
    cv::Mat green_roi = roi_mat - cv::Scalar(255,0,255);
    return green_roi;
}
cv::Mat roi::getRedRoi()
{
    cv::Mat red_roi = roi_mat - cv::Scalar(255,255,0);
    return red_roi;
}

double roi::getBlueMean(){
   m_blue_mean = cv::mean(roi::getBlueRoi());
   return m_blue_mean[0];
}
double roi::getGreenMean(){
   m_green_mean = cv::mean(roi::getGreenRoi());
   return m_green_mean[1];
}

double roi::getRedMean(){
   m_red_mean = cv::mean(roi::getRedRoi());
   return m_red_mean[2];
}

void roi::increaseIteration(void){
    m_iteration++;
}int roi::getIteration(){
    return m_iteration;
}

QVector<double> roi::getBlueVals(){

    if(m_iteration<450){
        m_blue_vals.append(m_blue_mean[0]);
    }
    else if (m_iteration>=450){
        for(int i=0;m_blue_vals.size();i++){
            if(i!=m_blue_vals.size()){
                m_blue_vals[i]=m_blue_vals[i+1];
            }else{
                m_blue_vals[i]=m_blue_mean[0];
            }
        }
    }
    return m_blue_vals;
}

QVector<double> roi::getIteratorVals(){
    if(m_iteration<450){
        m_iterator_vals.append(m_iteration);
    }
    else if (m_iteration>=450){
        for(int i=0;m_iterator_vals.size();i++){
            if(i!=m_iterator_vals.size()){
                m_iterator_vals[i]=m_iterator_vals[i+1];
            }else if (i==m_iterator_vals.size()){
                m_iterator_vals[i]=m_iteration;
            }
        }
    }
    return m_blue_vals;
}
