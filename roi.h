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
    cv::Mat getRoiMat();
    cv::Mat getBlueRoi();
    cv::Mat getGreenRoi();
    cv::Mat getRedRoi();

    double getBlueMean();
    double getGreenMean();
    double getRedMean();


    void increaseIteration(void);
    int getIteration(void);

    QVector<double> getBlueVals();
    QVector<double> getGreenVals();
    QVector<double> getRedVals();
    QVector<double> getIteratorVals();

private:
    cv::Scalar m_blue_mean;
    cv::Scalar m_green_mean;
    cv::Scalar m_red_mean;

    int m_iteration=0;

    QVector<double> m_blue_vals;
    QVector<double> m_green_vals;
    QVector<double> m_red_vals;
    QVector<double> m_iterator_vals;
};




#endif // ROI_H
