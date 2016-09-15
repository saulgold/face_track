#include "roi.h"

roi::roi()
{

}

roi::~roi(){

}

void roi::setRoiMat(Mat roiMat){
    roi_mat = roiMat;
}
void roi::setStaticRoi(cv::Mat frame){
    cv::Point face_position = getFacePosition();
    double face_width = getFaceWidth();

    cv::Rect rect = cv::Rect(face_position.x-10+(face_width/4.0),face_position.y,20,20);
    m_roi_rect = rect;
    roi_mat = cv::Mat(frame,rect);

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
    return this->m_blue_vals;
}
QVector<double> roi::getGreenVals(){
    return this->m_green_vals;
}

QVector<double> roi::getRedVals(){
    return this->m_red_vals;
}


QVector<double> roi::getIteratorVals(){
    return this->m_iterator_vals;
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
        for(int i=0;i<FRAME_SIZE-1;i++){

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

std::vector<double> roi::normalise(QVector<double> rgb_vals){

    int mean=0;
    int variance=0;
    int standard_deviation=0;
    cv::vector<double> output_vals;
    if(!rgb_vals.empty()){


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
            double norm_val = (rgb_vals[i]-mean);
            norm_val = norm_val/standard_deviation;

            output_vals.push_back(norm_val);
        }
    }
    return output_vals;
}
void roi::normaliseRGB(void){
   m_red_norm = normalise(m_red_vals);
   m_green_norm =  normalise(m_blue_vals);
   m_blue_norm= normalise(m_green_vals);
}

std::vector<double> roi::getRedNorm(){
    return this->m_red_norm;
}

std::vector<double> roi::getGreenNorm(){
    return this->m_green_norm;
}

std::vector<double> roi::getBlueNorm(){
    return this->m_blue_norm;
}

void roi::makePcaMatrix(std::vector<int> red, std::vector<int> green, std::vector<int> blue, cv::Mat pca_matrix){
    pca_matrix.row(0).setTo(red);
    pca_matrix.row(1).setTo(green);
    pca_matrix.row(2).setTo(blue);
}
 cv::Mat roi::createIcaMatrix(std::vector<double> red, std::vector<double> green, std::vector<double> blue){
     std::vector <vector <double> > vector_matrix;

     vector_matrix.push_back(red);
     vector_matrix.push_back(green);
     vector_matrix.push_back(blue);
      cv::Mat ica_matrix(3,vector_matrix.at(0).size(),CV_64FC1);

     for(int i=0; i<ica_matrix.rows; ++i){
          for(int j=0; j<ica_matrix.cols; ++j){
               ica_matrix.at<double>(i, j) = vector_matrix.at(i).at(j);
          }
     }
     return ica_matrix;

 }
void roi::setIcaMatrix(cv::Mat ica_matrix){
    this->m_ica_matrix = ica_matrix;
}
cv::Mat roi::getIcaMatrix(void){
    return this->m_ica_matrix;
}

void roi::setRemeanMatrix(cv::Mat input){

   cv::Mat mean,output;
   cv::reduce(input,mean,0,CV_REDUCE_AVG);
   cv::Mat temp = cv::Mat::ones(input.rows, 1, CV_64FC1);
   output=input-temp*mean;

   m_remean_matrix = output;
}

cv::Mat roi::getRemeanMatrix(void){
    return m_remean_matrix;
}

void roi::setWhitenMatrix(cv::Mat input){
    // need to be remean before whiten
   // qDebug()<<printMatTest(input);

    const int N=input.rows;  //num of data
    const int M=input.cols;  //dimention

     cv::Mat cov,output;
     cv::Mat D;
     cv::Mat E;
     cv::Mat temp=cv::Mat::eye(M,M,CV_64FC1);
     cv::Mat temp2;

     cov=input.t()*input/N;
    // qDebug()<<printMatTest(cov);
     cv::eigen(cov,D,E);
     cv::sqrt(D,D);
     //qDebug()<<printMatTest(D);

     for(int i=0;i<M;i++)
     { temp.at<double>(i,i)=D.at<double>(i,0);}

//     qDebug()<<printMatTest(temp);
//     qDebug()<<printMatTest(E);
//     qDebug()<<printMatTest(input);
//     qDebug()<<printMatTest(temp.inv());


//somethong wrong here, .inv gives nan - try normalising first
    // qDebug()<<"determinate"<<cv::determinant(temp);
     temp2=E*temp.inv()*E.t()*input.t();

    // qDebug()<<printMatTest(temp2);

    output=temp2.t();
   // qDebug()<<printMatTest(output);

    m_whiten_matrix = output;
}
cv::Mat roi::getWhitenMatrix(void){
    return m_whiten_matrix;
}
void roi::runIca(cv::Mat input,cv::Mat &output, cv::Mat &W, int snum)//output =Independent components matrix,W=Un-mixing matrix
{
    omp_set_dynamic(0);
    omp_set_num_threads(4);
   //qDebug()<< printMatTest(input);
    const  int M=input.rows;    // number of data
            const  int N=input.cols;    // data dimension

            const int maxIterations=100;
            const double epsilon=0.001;

            if(N<snum)
            { snum=M;
              printf(" Can't estimate more independent components than dimension of data ");}

           cv::Mat R(snum,N,CV_64FC1);
           cv::randn(R, cv::Scalar(0), cv::Scalar(1));
           cv::Mat ONE=cv::Mat::ones(M,1,CV_64FC1);

           for(int i=0;i<snum;++i)
           {
             qDebug()<<i;
             int iteration=0;
             cv::Mat P(1,N,CV_64FC1);
             R.row(i).copyTo(P.row(0));

              while(iteration<=maxIterations)
              {
                //qDebug()<<iteration;
                iteration++;
                cv::Mat P2;
                P.copyTo(P2);
                cv::Mat temp1,temp2,temp3,temp4;
                temp1=P*input.t();
                cv::pow(temp1,3,temp2);
                cv::pow(temp1,2,temp3);
                temp3=3*temp3;
                temp4=temp3*ONE;
                P=temp2*input/M-temp4*P/M;

                if(i!=0)
               {
                 cv::Mat temp5;
                 cv::Mat wj(1,N,CV_64FC1);
                 cv::Mat temp6=cv::Mat::zeros(1,N,CV_64FC1);

                 for(int j=0;j<i;++j)
                 {
                    R.row(j).copyTo(wj.row(0));
                    temp5=P*wj.t()*wj;
                    temp6=temp6+temp5;

                 }
                 P=P-temp6;
                }
                 double Pnorm=cv::norm(P,4);
                             P=P/Pnorm;

                 double j1=cv::norm(P-P2,4);
                 double j2=cv::norm(P+P2,4);
                 if(j1<epsilon || j2<epsilon)
                 {
                    P.row(0).copyTo(R.row(i));
                    std::vector<double> v;
                    QString s;
                    QChar c;
                    R.row(0).copyTo(v);
                    for (int i=0; i < v.size();i++){
                        s.push_back(QString::number(v[i]));

                        s.push_back(", ");
                    }
                    //qDebug()<<s;

                    break;
                  }
                  else if( iteration==maxIterations)
                  {
                      P.row(0).copyTo(R.row(i));
                      std::vector<double> v;
                      QString s;
                      QChar c;
                      R.row(0).copyTo(v);
                      for (int i=0; i < v.size();i++){
                          s.push_back(QString::number(v[i]));

                          s.push_back(", ");
                      }
                     //qDebug()<<s;

                  }
                }

}
              output=R*input.t();
    W=R;
}

//void roi::takePCA(cv::Mat matrix){
//    cv::PCA pca(matrix,cv::Mat(),CV_PCA_DATA_AS_ROW,3);
//    for(int i =0;<matrix.rows;i++){
//        pca.project(hj)
//    }
//}

void roi::setTestSignal(std::vector<double>input_signal){
    m_test_signal = input_signal;
}
std::vector<double> roi::getTestSignal(){
    return m_test_signal;
}
void roi::setIcaSignal(cv::Mat input){
    m_ica_signal = input;
}
cv::Mat roi::getIcaSignal(void){
    return m_ica_signal;
}

std::vector<double> roi::takeFFT(std::vector <double> signal){
    std::vector<double> output;

    int length = signal.size();
    std::vector<double> real_vector = signal;
    std::vector<double> imaginary_vector(length);
        if(!real_vector.empty()){
            Fft::transform(real_vector,imaginary_vector);
            m_red_fft.clear();
            for(int i=0;i<real_vector.size();i++){
                output.push_back( std::sqrt(std::pow(real_vector[i],2)+std::pow(imaginary_vector[i],2)));
            }

        }
    return output;
//    int c = m_red_vals.size();
//    cv::Mat input = Mat::zeros(1,c,CV_8UC1);
//    cv::Mat output = Mat::zeros(1,c, CV_8UC1);
//    input.row(0).setTo( m_red_vals.toStdVector());

  //  cv::dft(input,output,DFT_ROWS);
    //cv::dft(m_green_vals.toStdVector(),m_green_frequency);
    //cv::dft(m_blue_vals.toStdVector(),m_blue_frequency);
}

void roi::takeFFTICA(cv::Mat ica_matrix){

    std::vector<double> ica_red,ica_green,ica_blue;

    ica_matrix.row(0).copyTo(ica_red);
    ica_matrix.row(1).copyTo(ica_green);
    ica_matrix.row(2).copyTo(ica_blue);

    m_red_fft = takeFFT(ica_red);
    m_green_fft = takeFFT(ica_green);
    m_blue_fft = takeFFT(ica_blue);

}
std::vector<double> roi::getRedFft(){
    return m_red_fft;
}

std::vector<double> roi::getBlueFft(){
    return m_blue_fft;
}

std::vector<double> roi::getGreenFft(){
    return m_green_fft;
}

void roi::update(){
    this->setRgbRois();
    this->updateMeans();
    this->updateVals2();
}

QString roi::printMatTest(cv::Mat input){
    std::vector<double> v,v2,v3;
    QString s;
    input.row(0).copyTo(v);
    input.row(1).copyTo(v2);
    input.row(2).copyTo(v3);

    for (int i=0; i < v.size();i++){
        s.push_back(QString::number(v[i]));

        s.push_back(", ");
    }
    s.push_back("newline");
    for (int i=0; i < v.size();i++){
        s.push_back(QString::number(v2[i]));

        s.push_back(", ");
    }
    s.push_back("newline");
    for (int i=0; i < v.size();i++){
        s.push_back(QString::number(v3[i]));

        s.push_back(", ");
    }
    return s;
}
std::vector<double> roi::generateSinWave(int freq){
    std::vector<double> output;
    int frame_size = FRAME_SIZE;
    for(int i=0; i<frame_size;i++){
        output.push_back(std::sin(freq*2*3.14* i ));

    }
    return output;
}

void roi::setCodeTimer(double time){
    m_frame_time = time;
}

double roi::getCodeTimer(){
    return m_frame_time;
}

//returns the bin location of the maximum frequency
double roi::findMax(std::vector<double> input){
    int buffer =0;
    int max = 0;
    for(int i=0;i<input.size();i++){
        if(input[i]>buffer){
            buffer = input[i];
            max = i;
        }
    }
    return max;
}
double roi::convertToHz(double input){
    double frame_length = FRAME_SIZE;
    double frame_time = getCodeTimer();
    double Fs = frame_length/(2*frame_time);
    double output;
    output= (input * frame_time)/frame_length;
    return output;
}

std::vector<double> roi::createPowerSpectrum(std::vector<double> fft_vector){
    double frame_length = FRAME_SIZE;
    double frame_time = getCodeTimer();
    double Fs = frame_length/(2*frame_time);
    std::vector<double> output;

    for(int i=0;i<frame_length/2;i++){
        output.push_back( (i * frame_time)/frame_length);
    }
    //to pad out vector so it's the same length as othervectors
    //this helps when saving data to file
    for(int i= frame_length/2; i<frame_length;i++){
        output.push_back(0);
    }
    m_power_spectrum = output;
    return output;
}

void roi::findMaxFft(std::vector<double> input){
    double maxf=0;
    double frame_size = FRAME_SIZE;
    double bufferf =0;
    int pos=0;
    std::vector<double> freq;
    for(double i =1;i<input.size()/2;i++){
        freq.push_back((i* 60*61)/(frame_size));
    }

    for(int i =0;i<input.size()/2;i++){
       if((input[i]>bufferf)&&(freq[i]>30)&&(freq[i]<120)){
          bufferf = input[i];
           maxf = freq[i];
           pos=i;
       }
    }

    m_bpm = maxf;
}

double roi::getBpm(){
    return m_bpm;
}




