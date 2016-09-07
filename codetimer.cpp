#include "codetimer.h"

codetimer::codetimer()
{

}

void codetimer::startTimer(void)
{
    if(m_flag==0){
        m_start_time = cv::getTickCount();
        m_flag=1;
    }
}

void codetimer::endTimer(void){
    m_end_time=cv::getTickCount();
}

double codetimer::getTime(void){
    if(m_flag==1){
        m_frame_time = (m_end_time-m_start_time)/cv::getTickFrequency();

        m_flag=0;
        return m_frame_time;
    }
}
