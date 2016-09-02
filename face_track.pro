#-------------------------------------------------
#
# Project created by QtCreator 2016-07-22T15:50:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = face_track
TEMPLATE = app

QMAKE_CXXFLAGS += -openmp -arch:AVX -D "_CRT_SECURE_NO_WARNINGS"
#QMAKE_LFLAGS +=/STACK:64000000

SOURCES += main.cpp\
        mainwindow.cpp \
    VideoFaceDetector.cpp \
    qcustomplot.cpp \
    roi.cpp \
    fft.cpp

HEADERS  += mainwindow.h \
    VideoFaceDetector.h \
    recursive_ica.h \
    sys_lib.h \
    qcustomplot.h \
    roi.h \
    fft.h

FORMS    += mainwindow.ui

INCLUDEPATH += C:\\opencv2413\\build\\include \
               C:\\opencv2413\\build\\include\\opencv \
               C:\\opencv2413\\build\\include\\opencv2

CONFIG(Debug) {
LIBS += -LC:\opencv2413\build\x86\vc12\lib \
    -lopencv_imgproc2413d \
    -lopencv_objdetect2413d \
    -lopencv_photo2413d \
    -lopencv_video2413d \
    -lopencv_calib3d2413d \
    -lopencv_core2413d \
    -lopencv_features2d2413d \
    -lopencv_flann2413d \
    -lopencv_ml2413d \
    -lopencv_imgproc2413d \
    -lopencv_contrib2413d \
    -lopencv_highgui2413d
} else {
LIBS += -LC:\opencv2413\build\x86\vc12\lib \
    -lopencv_imgproc2413 \
    -lopencv_objdetect2413 \
    -lopencv_photo2413 \
    -lopencv_video2413 \
    -lopencv_calib3d2413 \
    -lopencv_core2413 \
    -lopencv_features2d2413 \
    -lopencv_flann2413 \
    -lopencv_ml2413 \
    -lopencv_imgproc2413 \
    -lopencv_contrib2413 \
    -lopencv_highgui2413
}

