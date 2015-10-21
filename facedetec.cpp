#include "facedetec.h"
#include "facedetect-dll.h"
#pragma comment(lib,"libfacedetect.lib")

facedetec::facedetec()
{
    this->faceResult = NULL;
}

facedetec::~facedetec()
{
    this->faceResult = NULL;
}

void facedetec::Detecface(QString &path)
{
    string rotepath;
    if(path.isEmpty())
    {
        qDebug()<< "func facedetec::Detecface()  check if(path.isEmpty())";
        return;
    }
    rotepath = path.toStdString();
    this->imageSrc.release();
    Mat frame = imread(rotepath);
    this->imageSrc = frame.clone();
    if(this->faceResult)
    {
        free(this->faceResult);
        this->faceResult = NULL;
    }
    this->BaseDetec(frame, &(this->faceResult));
    this->DrawFace(frame, this->faceResult);
    waitKey(30);


}


void facedetec::BaseDetec(Mat &frame, int **result)
{
    if(!frame.data)
    {
        qDebug() << "func facedetec::BaseDetec() check  if(!frame.data)";
        return;
    }
    int *pResult = NULL;
    Mat gray = frame.clone();
    cvtColor(gray,gray,CV_BGR2GRAY);

    if(this->faceResult != NULL)
    {
        free(this->faceResult);
        this->faceResult = NULL;
    }
    pResult = facedetect_frontal((unsigned char*)(gray.ptr(0)), gray.cols, gray.rows, gray.step,
                                          1.2f, 2,  24);
    *result = pResult;
    pResult = NULL;
}

void facedetec::VideoDetecFace(int deiverId)
{
    VideoCapture cap(deiverId);
    if(cap.isOpened())
    {
        Mat frame;
        while(true)
        {
            int *result =NULL;
            cap >> frame;
            this->BaseDetec(frame, &result);
            this->DrawFace(frame, result);
            char key = (char) waitKey(20);
            if(key == 27)
                break;
        }
    }
}

void facedetec::DrawFace(Mat& frame, int *result)
{
    for(int i = 0; i < (result ? *result : 0); i++)
    {
        short * p = ((short*)(result+1))+6*i;
        int x = p[0];
        int y = p[1];
        int w = p[2];
        int h = p[3];

        Rect face_i = Rect(x, y, w, h);
        rectangle(frame, face_i, CV_RGB(0, 255,0), 1);
    }
    imshow("face", frame);
}

int facedetec::SavePhoto(Mat& frame, int *result, QString &path, int width, int height)
{
    int rect = 0;
    if(path.isEmpty() || !frame.data)
    {
        qDebug() << "func facedetec::SavePhoto() check  if(path.isEmpty())";
        rect = -1;
        return rect;
    }
    path = path + "/";
    for(int i = 0; i < (result ? *result : 0); i++)
    {
        short * p = ((short*)(result+1))+6*i;
        int x = p[0];
        int y = p[1];
        int w = p[2];
        int h = p[3];

        Rect face_i = Rect(x, y, w, h);
        Mat face = frame(face_i);
        Mat resized;
        //cvtColor(frame(face_i), frame(face_i), CV_BGR2GRAY);
        cvtColor(face, face, CV_BGR2GRAY);
        cv::resize(face, resized, Size(width, height), CV_INTER_AREA);
        QString s = QString::number(i+1) + ".jpg";
        QString rout = path + s;
        imwrite(rout.toStdString(), resized);
        s.clear();
        rout.clear();
    }
    return rect;
}


int facedetec::SaveFace(QString path)
{
    int rect = 0;
    rect = this->SavePhoto(this->imageSrc, this->faceResult, path);

    return rect;
}
