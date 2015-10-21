#ifndef FACEDETEC_H
#define FACEDETEC_H

#include <QString>
#include <QDebug>
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

private:
    void BaseDetec(Mat& frame, int **result);

    int *faceResult;
    Mat imageSrc;

};

#endif // FACEDETEC_H
