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

    std::vector<int> normalise(QVector<double> rgb_vals);
    void makePcaMatrix(std::vector<int> red, std::vector<int> green, std::vector<int> blue, Mat pca_matrix);
    void normaliseRGB(void);
    void takeFFT(void);

    void update();
    QVector<double> getBlueVals();
    QVector<double> getGreenVals();
    QVector<double> getRedVals();
    QVector<double> getIteratorVals();

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

    cv::Mat m_red_frequency;
    cv::Mat m_green_frequency;
    cv::Mat m_blue_frequency;
};




#endif // ROI_H
