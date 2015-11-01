#-------------------------------------------------
#
# Project created by QtCreator 2015-10-21T10:36:26
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FaceColect
TEMPLATE = app

INCLUDEPATH += D:/OpenCVSrc/opencv/build/include/
INCLUDEPATH += D:/OpenCVSrc/opencv/build/include/opencv/
INCLUDEPATH += D:/OpenCVSrc/opencv/build/include/opencv2/

INCLUDEPATH += D:/LibFaceDetection/include
LIBS += -LD:/LibFaceDetection/lib -llibfacedetect

win32:CONFIG(debug, debug|release):{
LIBS += -LD:/OpenCVSrc/opencv/build/x86/vc11/lib \
-lopencv_core2410d \
-lopencv_imgproc2410d \
-lopencv_highgui2410d \
-lopencv_ml2410d \
-lopencv_video2410d \
-lopencv_features2d2410d \
-lopencv_calib3d2410d \
-lopencv_objdetect2410d \
-lopencv_contrib2410d \
-lopencv_legacy2410d \
-lopencv_gpu2410d \
-lopencv_nonfree2410d \
-lopencv_ocl2410d \
-lopencv_photo2410d \
-lopencv_stitching2410d \
-lopencv_superres2410d \
-lopencv_ts2410d \
-lopencv_videostab2410d \
-lopencv_flann2410d
}else:win32:CONFIG(release, debug|release): {
LIBS += -LD:/OpenCVSrc/opencv/build/x86/vc11/lib \
-lopencv_core2410 \
-lopencv_imgproc2410 \
-lopencv_highgui2410 \
-lopencv_ml2410 \
-lopencv_video2410 \
-lopencv_features2d2410 \
-lopencv_calib3d2410 \
-lopencv_objdetect2410 \
-lopencv_contrib2410 \
-lopencv_legacy2410 \
-lopencv_gpu2410 \
-lopencv_nonfree2410 \
-lopencv_ocl2410 \
-lopencv_photo2410 \
-lopencv_stitching2410 \
-lopencv_superres2410 \
-lopencv_ts2410 \
-lopencv_videostab2410 \
-lopencv_flann2410
}


SOURCES += main.cpp\
        mainwindow.cpp \
    facedetec.cpp \
    facerecognize.cpp \
    login.cpp \
    connection.cpp

HEADERS  += mainwindow.h \
    facedetect-dll.h \
    facedetec.h \
    facerecognize.h \
    login.h \
    connection.h \
    dbconnection.h

FORMS    += mainwindow.ui \
    login.ui

RESOURCES += \
    qrc.qrc
