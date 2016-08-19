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
    m_blue_mean = cv::mean(this->getBlueRoi());
    m_green_mean = cv::mean(this->getGreenRoi());
    m_red_mean = cv::mean(this->getRedRoi());

}
void roi::updateVals(){
    m_blue_vals.append(m_blue_mean[0]);
    m_green_vals.append(m_green_mean[1]);
    m_red_vals.append(m_red_mean[2]);

    m_iterator_vals.append(m_iteration);

    if(m_iteration%FRAME_SIZE==0){
       m_blue_vals.clear();
       m_green_vals.clear();
       m_red_vals.clear();
       m_iterator_vals.clear();
    }

}

void roi::updateVals2(){
    if(m_iteration<FRAME_SIZE){
        m_blue_vals.append(m_blue_mean[0]);
        m_green_vals.append(m_green_mean[1]);
        m_red_vals.append(m_red_mean[2]);

        m_iterator_vals.append(m_iteration);
    }
    else if (m_iteration>=FRAME_SIZE){
        for(int i=0;i<FRAME_SIZE-2;i++){

                m_blue_vals[i]=m_blue_vals[i+1];
                m_green_vals[i]=m_green_vals[i+1];
                m_red_vals[i]=m_red_vals[i+1];
                m_iterator_vals[i]=m_iterator_vals[i+1];

        }
        m_blue_vals.pop_back();
        m_green_vals.pop_back();
        m_red_vals.pop_back();
        m_iterator_vals.pop_back();
        m_blue_vals.push_back(m_blue_mean[0]);
        m_green_vals.push_back(m_green_mean[1]);
        m_red_vals.push_back(m_red_mean[2]);
        m_iterator_vals.push_back(m_iteration);
    }

}

//void roi::normalise(void){
//    cv::normalize()
//}

std::vector<int> roi::normalise(QVector<double> rgb_vals){

    int mean=0;
    int variance=0;
    int standard_deviation=0;
    cv::vector<int> output_vals;

    //find mean
    for(int i =0;i<rgb_vals.size();i++){
        mean += rgb_vals[i];
    }
    mean = mean / rgb_vals.size();
    //find standard deviation
    for(int i =0;i<rgb_vals.size();i++){
        variance += std::pow(rgb_vals[i] - mean,2);
    }
    standard_deviation=std::sqrt(variance);

    //normalise
    for(int i = 0; i<rgb_vals.size();i++){

        output_vals.push_back((rgb_vals[i]-mean)/standard_deviation);
    }
    return output_vals;
}
void normaliseRGB(void){
    normalise(m_red_vals);
    normalise(m_blue_vals);
    normalise(m_green_vals);
}

void roi::makePcaMatrix(std::vector<int> red, std::vector<int> green, std::vector<int> blue, cv::Mat pca_matrix){
    pca_matrix.row(0).setTo(red);
    pca_matrix.row(1).setTo(green);
    pca_matrix.row(2).setTo(blue);
}
void roi::takePCA(cv::Mat matrix){
    cv::PCA pca(matrix,cv::Mat(),CV_PCA_DATA_AS_ROW,3);
    for(int i =0;<matrix.rows;i++){
        pca.project(hj)
    }
}

void roi::update(){
    this->setRgbRois();
    this->updateMeans();
    this->updateVals();
}
