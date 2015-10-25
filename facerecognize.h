#ifndef FACERECOGNIZE_H
#define FACERECOGNIZE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "facedetec.h"

using namespace std;
using namespace cv;



class facerecognize
{
public:
    facerecognize();
    ~facerecognize();

    /*使用CSV文件去读图像和标签，主要使用stringstream和getline方法*/
    static void read_csv(const String& filename, vector<Mat>& images,
                         vector<int>& labels, char separator =';')
    {

        std::ifstream file(filename.c_str(), ifstream::in);
           if (!file) {
               string error_message ="No valid input file was given, please check the given filename.";
               CV_Error(CV_StsBadArg, error_message);
           }
           string line, path, classlabel;
           while (getline(file, line)) {
               stringstream liness(line);
               getline(liness, path, separator);
               getline(liness, classlabel);
               if(!path.empty()&&!classlabel.empty()) {
                   images.push_back(imread(path, 0));
                   labels.push_back(atoi(classlabel.c_str()));
               }
           }
    }
    int Learn(QString& path);

    void PhotoRecognize(QString imagepath);

    void VideoRecognize(int driverId);

    void DrawFaceMark(cv::Mat &image, int *result, std::vector<int> &list);

    void LoadTrainFile(QString& path);

    void SetWidthAndHeight(int width = 92, int height = 112);

private:
    void Recognize(cv::Mat &image, int *result, std::vector<int>& list);

    std::vector<cv::Mat> images;

    std::vector<int> labels;

    std::vector<int> numlist;

    Ptr<FaceRecognizer> model;
    facedetec *faceDetec;
    QString  output_folder;

    bool loaded;

    bool readcsved;

    int im_width;
    int im_height;

    map<int, string> mapint;
};

#endif // FACERECOGNIZE_H
