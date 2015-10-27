#include "facedetec.h"
#include "facedetect-dll.h"
#pragma comment(lib,"libfacedetect.lib")

facedetec::facedetec()
{
    this->faceResult = NULL;
    this->startCloecFace = false;
}

facedetec::~facedetec()
{
    this->faceResult = NULL;
    this->startCloecFace = false;
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

    if(this->faceResult != NULL)
    {
        //free(this->faceResult);
        this->faceResult = NULL;
    }

    this->BaseDetec(frame, &(this->faceResult));
    this->DrawFace(frame, this->faceResult);
    char key = (char) waitKey(20);
    if(key == 27)
        return;

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
    /***************************
     * 这个已经在Detecface中有了
     * jhz 10.26.2015
    if(this->faceResult != NULL)
    {
        //free(this->faceResult);
        this->faceResult = NULL;
    }
    */

    pResult = facedetect_frontal((unsigned char*)(gray.ptr(0)), gray.cols, gray.rows, gray.step,
                                          1.2f, 2,  24);
    *result = pResult;
    pResult = NULL;
}

void facedetec::VideoDetecFace(int deiverId)
{
    int  num = 0;
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
            if(this->startCloecFace)
            {
                num++;
                this->VideoSavePhoto(frame, result, this->videoColectPath, num);
                qDebug() << num;
                //采集20张头像
                if(num == 20)
                {
                    this->startCloecFace = false;
                    break;
                }
            }
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
        rectangle(frame, face_i, CV_RGB(0, 255,0), 2);
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

/********************************************
 * 为摄像采集人脸的保存人脸函数
 *
 * @param: Mat &frmae : 图像
 * @param：int *result : 检测到人人脸坐标 信息
 * @param: QString path: 文件存放绝对路径
 * @param: int num: 头像的标号
 * @param: int vwidth: 头像宽 默认为92
 * @param: int vheight:头像高 默认为112
 * ******************************************/
void facedetec::VideoSavePhoto(Mat &frame, int *result, QString path, int num, int vwidth, int vheight)
{
    if(path.isEmpty() || !frame.data)
    {
        qDebug() << "func facedetec::VideoSavePhoto() check  if(path.isEmpty())";
        return;
    }
    QString snum = QString::number(num);
    QString fpath = path + "/" + snum + ".jpg";

    if(result ? *result : 0)
    {
        short * p = ((short*)(result+1));
        int x = p[0];
        int y = p[1];
        int w = p[2];
        int h = p[3];

        Rect face_i = Rect(x, y, w, h);
        Mat face = frame(face_i);
        Mat resized;

        cvtColor(face, face, CV_BGR2GRAY);
        cv::resize(face, resized, Size(vwidth, vheight), CV_INTER_AREA);
        imwrite(fpath.toStdString(), resized);
        snum.clear();
        fpath.clear();
    }
}

int facedetec::SaveFace(QString path)
{
    int rect = 0;
    /*调用核心存储函数*/
    rect = this->SavePhoto(this->imageSrc, this->faceResult, path);

    return rect;
}

void facedetec::VideoFaceColect(Mat& frame, int *result, QString &path)
{
    int     ret = 0;
    QDir    dir;
    if(path.isEmpty())
    {
        qDebug() << "func facedetec::VideoFaceColect()  check if(path.isEmpty())";
        return;
    }

    /*如果文件夹不存在则创建文件夹*/
    if(!dir.exists(path))
    {
       ret = dir.mkdir(path);
       if(ret != 0)
       {
           qDebug() << "func facedetec::VideoFaceColect() mkdir error err: " << ret;
           return;
       }
    }
    /*存储头像*/
    this->SavePhoto(frame, result, path);
}

void facedetec::SetVideoColectPath(QString &path)
{
    if(path.isEmpty())
    {
        qDebug() << "func facedetec::SetVideoColectPath()  check if(path.isEmpty())";
        return;
    }
    this->videoColectPath = path;
}

void facedetec::SetStartCloecFace(bool flag)
{
    this->startCloecFace = flag;
}

void facedetec::VideoCollectInit(QString &path, bool flag)
{
    this->SetVideoColectPath(path);
    this->SetStartCloecFace(flag);
}
