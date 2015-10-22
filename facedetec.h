#ifndef FACEDETEC_H
#define FACEDETEC_H

#include <QString>
#include <QDebug>
#include <QDir>
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"

#include "iostream"
#include "string"
#include "string.h"


using namespace std;
using namespace cv;

class facedetec
{
public:
    facedetec();
    ~facedetec();

    void Detecface(QString& path);

    void Detecface(Mat& frame, int **result);

    void VideoDetecFace(int deiverId = 0);

    void DrawFace(Mat&frame, int* result);

    //给用户的Save
    int SaveFace(QString path);

    int SavePhoto(Mat& frame, int *result, QString& path, int width = 92, int height = 112);
    /*为摄像采集人脸的保存人脸函数*/
    void VideoSavePhoto(Mat& frame, int *result, QString path, int num, int vwidth = 92, int vheight = 112);

    void VideoCollectInit(QString& path, bool flag);

    void SetVideoColectPath(QString& path);
    void SetStartCloecFace(bool flag);

private:
    void BaseDetec(Mat& frame, int **result);
    //摄像头人脸采集函数
    void VideoFaceColect(Mat& frame, int *result, QString& path);

    int *faceResult;
    Mat imageSrc;

    //摄像头采集标识符(默认为false)
    bool startCloecFace;
    //头像存放路径
    QString videoColectPath;

};

#endif // FACEDETEC_H
