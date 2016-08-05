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
    return m_blue_roi;

}
cv::Mat roi::getGreenRoi()
{
    return m_green_roi;
}
cv::Mat roi::getRedRoi()
{
    return m_red_roi;
}

double roi::getBlueMean(){
   return m_blue_mean[0];
}
double roi::getGreenMean(){
   return m_green_mean[1];
}

double roi::getRedMean(){
   return m_red_mean[2];
}

void roi::increaseIteration(void){
    m_iteration++;
}int roi::getIteration(){
    return m_iteration;
}

void roi::updateBlueVals(){

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

}
QVector<double> roi::getBlueVals(){
    return m_blue_vals;
}
QVector<double> roi::getGreenVals(){
    return m_green_vals;
}

QVector<double> roi::getRedVals(){
    return m_red_vals;
}


QVector<double> roi::getIteratorVals(){
    return m_iterator_vals;
}
void roi::setRgbRois(){
    m_blue_roi = roi_mat - cv::Scalar(0,255,255);
    m_green_roi = roi_mat - cv::Scalar(255,0,255);
    m_red_roi = roi_mat - cv::Scalar(255,255,0);

}

void roi::updateMeans(){
    m_blue_mean = cv::mean(roi::getBlueRoi());
    m_green_mean = cv::mean(roi::getGreenRoi());
    m_red_mean = cv::mean(roi::getRedRoi());

}
void roi::updateVals(){
    if(m_iteration<FRAME_SIZE){
        m_blue_vals.append(m_blue_mean[0]);
        m_green_vals.append(m_green_mean[1]);
        m_red_vals.append(m_red_mean[2]);

        m_iterator_vals.append(m_iteration);
    }
    else if (m_iteration>=FRAME_SIZE){
        for(int i=0;m_iterator_vals.size();i++){
            if(i!=m_iterator_vals.size()){
                m_blue_vals[i]=m_blue_vals[i+1];
                m_green_vals[i]=m_green_vals[i+1];
                m_red_vals[i]=m_red_vals[i+1];
                m_iterator_vals[i]=m_iterator_vals[i+1];
            }else{
                m_blue_vals[i]=m_blue_mean[0];
                m_green_vals[i]=m_green_mean[1];
                m_red_vals[i]=m_red_mean[2];
                m_iterator_vals[i]=m_iteration;
            }
        }
    }
}

void roi::update(){
    setRgbRois();
    updateMeans();
    updateVals();
}
