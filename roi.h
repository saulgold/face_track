#ifndef ROI_H
#define ROI_H
#include "mainwindow.h"

class roi
{
public:
    roi();
    ~roi();

    cv::Mat roi_mat;
    void setFacePosition(cv::Point p){m_face_position = p;}
    cv::Point getFacePosition(){return m_face_position;}
    void setFaceWidth(double w){m_face_width = w;}
    double getFaceWidth(){return m_face_width;}
    void setRoiMat(cv::Mat roiMat);
    void setStaticRoi(cv::Mat frame);
    cv::Rect getRect(){return m_roi_rect;}

    void setRgbRois();
    void updateMeans();
    void updateVals();
    void updateVals2();

    cv::Mat getRoiMat();
    cv::Mat getBlueRoi();
    cv::Mat getGreenRoi();
    cv::Mat getRedRoi();

    double getBlueMean();
    double getGreenMean();
    double getRedMean();


    void increaseIteration(void);
    int getIteration(void);

    void updateBlueVals();
    void updateGreenVals();
    void updateRedVals();

    std::vector<double> normalise(QVector<double> rgb_vals);
    void makePcaMatrix(std::vector<int> red, std::vector<int> green, std::vector<int> blue, Mat pca_matrix);
    void normaliseRGB(void);

    void update();
    QVector<double> getBlueVals();
    QVector<double> getGreenVals();
    QVector<double> getRedVals();
    QVector<double> getIteratorVals();

    std::vector<double> getRedNorm();
    std::vector<double> getGreenNorm();
    std::vector<double> getBlueNorm();

    void setTestSignal(std::vector<double>input_signal);
    std::vector<double> getTestSignal();
    //creates icamatrix where rgb components are rows
    cv::Mat createIcaMatrix(std::vector<double> red, std::vector<double> green, std::vector<double> blue); //create ica matrix from normalised signals
    void setIcaMatrix(cv::Mat ica_matrix);
    cv::Mat getIcaMatrix(void);
    void setRemeanMatrix(cv::Mat input);
    cv::Mat getRemeanMatrix(void);

    void setWhitenMatrix(cv::Mat input);
    cv::Mat getWhitenMatrix(void);
    void runIca(cv::Mat input,cv::Mat &output, cv::Mat &W, int snum);//output =Independent components matrix,W=Un-mixing matrix
    void setIcaSignal(cv::Mat input);
    cv::Mat getIcaSignal(void);
    QString printMatTest(cv::Mat input);
    std::vector<double> takeFFT(std::vector<double> signal);

    void roi::takeFFTICA(cv::Mat ica_matrix);
    std::vector<double> getRedFft();
    std::vector<double> getGreenFft();
    std::vector<double> getBlueFft();

    std::vector<double> roi::generateSinWave(int freq);
    void setCodeTimer(double time);
    double getCodeTimer();
    double findMax( std::vector<double> input);
    vector<double> roi::createPowerSpectrum(std::vector<double> fft_vector);
    double convertToHz(double input);
    void findMaxFft(std::vector<double> input);
    double getBpm();

private:
    cv::Mat m_ica_signal;
    cv::Mat m_whiten_matrix;
    cv::Mat m_remean_matrix;
    cv::Mat m_blue_roi;
    cv::Mat m_green_roi;
    cv::Mat m_red_roi;

    cv::Scalar m_blue_mean;
    cv::Scalar m_green_mean;
    cv::Scalar m_red_mean;
    cv::Mat m_normalised_mat;
    int m_iteration=0;

    QVector<double> m_blue_vals;
    QVector<double> m_green_vals;
    QVector<double> m_red_vals;
    QVector<double> m_iterator_vals;

    std::vector<double> m_red_norm;
    std::vector<double> m_green_norm;
    std::vector<double> m_blue_norm;


    std::vector<double> m_red_fft;
    std::vector<double> m_green_fft;
    std::vector<double> m_blue_fft;


    std::vector<double> m_test_signal;
    cv::Mat m_red_frequency;
    cv::Mat m_green_frequency;
    cv::Mat m_blue_frequency;

    cv::Mat m_ica_matrix;

    std::vector<double> m_sin_wave;

    double m_frame_time;
    std::vector<double> m_power_spectrum;
    double m_bpm;

   cv::Point m_face_position;
   double m_face_width;
   cv::Rect m_roi_rect;

};




#endif // ROI_H
