#ifndef ROI_H
#define ROI_H
#include "mainwindow.h"

class roi
{
public:
    roi();
    ~roi();

    cv::Mat roi_mat;



    void setRoiMat(cv::Mat roiMat);
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

    std::vector<float> normalise(QVector<double> rgb_vals);
    void makePcaMatrix(std::vector<int> red, std::vector<int> green, std::vector<int> blue, Mat pca_matrix);
    void normaliseRGB(void);
    void takeFFT(void);

    void update();
    QVector<double> getBlueVals();
    QVector<double> getGreenVals();
    QVector<double> getRedVals();
    QVector<double> getIteratorVals();

    std::vector<float> getRedNorm();
    std::vector<float> getGreenNorm();
    std::vector<float> getBlueNorm();

    std::vector<double> getRedFft();
    void setTestSignal(std::vector<double>input_signal);
    std::vector<double> getTestSignal();
private:
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

    std::vector<float> m_red_norm;
    std::vector<float> m_green_norm;
    std::vector<float> m_blue_norm;


    std::vector<double> m_red_fft;
    std::vector<double> m_test_signal;
    cv::Mat m_red_frequency;
    cv::Mat m_green_frequency;
    cv::Mat m_blue_frequency;
};




#endif // ROI_H
