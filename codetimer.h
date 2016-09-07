#ifndef CODETIMER_H
#define CODETIMER_H
#include "mainwindow.h"

class codetimer
{
public:
    codetimer();

    void startTimer(void);
    void endTimer(void);
    double getTime(void);
private:
    double m_start_time;
   double m_end_time;
    double m_frame_time;
    int m_flag;
};

#endif // CODETIMER_H
