#include "facerecognize.h"

facerecognize::facerecognize()
{
    this->model =  createFisherFaceRecognizer(20);
    //this->model = createLBPHFaceRecognizer(1, 5, 5, 5);
    this->faceDetec = new facedetec();
    this->loaded = false;
    this->readcsved = false;

    this->im_width = 92;
    this->im_height = 112;

    this->output_folder = "./face.xml";

    mapint[1] = "WL";
    mapint[2] = "JHZ";
    mapint[3] = "XSY";
    mapint[4] = "ZZC";
    mapint[5] = "CZM";
    mapint[6] = "XD";
    mapint[7] = "YYF";
    mapint[8] = "WYQ";
    mapint[9] = "YY";

}

facerecognize::~facerecognize()
{
    if(this->faceDetec)
    {
        delete this->faceDetec;
    }

    this->loaded = false;
    this->readcsved = false;
}

void facerecognize::SetWidthAndHeight(int width, int height)
{
    if(this->readcsved == false)
    {
        this->im_width = width;
        this->im_height = height;
    }
}

int facerecognize::Learn(QString& path)
{
    int     ret = 0;
    string csvFile = path.toStdString();
    try{
        this->read_csv(csvFile, this->images, this->labels);
        this->readcsved = true;
    } catch(cv::Exception& e) {
        cerr << "Error opening file" << csvFile << ". Reason: "<< e.msg << endl;
        ret = -1;
        exit(1);
    }

    if(this->images.size() <= 1)
    {
        ret = -2;
        QString error_message ="This demo needs at least 2 images to work.\
           Please add more images to your data set!";
        qDebug() << error_message << ret;
        return ret;
    }

    if(this->model)
    {
        this->model->train(this->images, this->labels);
        this->model->save(this->output_folder.toStdString());
        return ret;
    }
    else
    {
        ret = -3;
        qDebug() << "func facerecognize::Learn() check if(this->model)" << ret;
        return ret;
    }

}

void facerecognize::LoadTrainFile(QString& path)
{
    if(this->model && !(this->loaded))
    {
        this->model->load(path.toStdString());
        this->loaded = true;
    }
}

void facerecognize::VideoRecognize(int driverId)
{
    std::vector<int>      list;

    if(!this->model || !this->faceDetec)
    {
        int  ret = -1;
        qDebug() << "func facerecognize::VideoRecognize() check if(!this->model || !this->faceDetec) ret:"<<ret;
        return;
    }
    this->LoadTrainFile(QString("./face.xml"));

    VideoCapture cap(driverId);
    if(cap.isOpened())
    {
        Mat frame;
        while(true)
        {
            int *result =NULL;
            list.clear();
            cap >> frame;

            this->faceDetec->BaseDetec(frame, &result);
            this->Recognize(frame, result, list);
            //this->DrawFaceMark(frame, result, list);
            char key = (char) waitKey(20);
            if(key == 27)
                break;
        }
    }
}

void facerecognize::Recognize(Mat &image, int *result, std::vector<int>& list)
{
    Mat original = image;
    Mat gray;
    std::vector<int>  plist;

    cvtColor(original, gray, CV_BGR2GRAY);

    for(int i = 0; i < (result ? *result : 0); i++)
    {
        short * p = ((short*)(result+1))+6*i;
        int x = p[0];
        int y = p[1];
        int w = p[2];
        int h = p[3];

        Rect face_i = Rect(x, y, w, h);
        Mat face = gray(face_i);
        Mat face_resized;
        cv::resize(face, face_resized,
                   Size(this->im_width, this->im_height),
                   0, 0, INTER_LINEAR
                   );

        int prediction = this->model->predict(face_resized);
        plist.push_back(prediction);

        string box_text;
        //box_text = format("Prediction = ");
        rectangle(image, face_i, CV_RGB(0, 255,0), 2);
        if(prediction >= 0)
        {
            box_text.append( this->mapint[prediction] );
        }
        else
        {
            box_text.append( "Unknown" );
        }
        int pos_x = std::max(face_i.tl().x - 10, 0);
        int pos_y = std::max(face_i.tl().y - 10, 0);

        putText(image, box_text, Point(pos_x, pos_y),
                FONT_HERSHEY_PLAIN, 1.0,
                CV_RGB(0,255,0), 2.0
                );

    }

    list = plist;
    imshow("rec", image);
}


void facerecognize::DrawFaceMark(Mat &image, int *result, std::vector<int> &list)
{
    string box_text;
    box_text = format("Prediction = ");
    for(int i = 0; i < (result ? *result : 0); i++)
    {
        short * p = ((short*)(result+1))+6*i;
        int x = p[0];
        int y = p[1];
        int w = p[2];
        int h = p[3];

        Rect face_i = Rect(x, y, w, h);
        rectangle(image, face_i, CV_RGB(0, 255,0), 2);

        int num = list[i];
        if(num >= 0)
        {
            box_text.append( this->mapint[num] );
        }
        else
        {
            box_text.append( "Unknown" );
        }

        int pos_x = std::max(face_i.tl().x - 10, 0);
        int pos_y = std::max(face_i.tl().y - 10, 0);

        putText(image, box_text, Point(pos_x, pos_y),
                FONT_HERSHEY_PLAIN, 1.0,
                CV_RGB(0,255,0), 2.0
                );
    }
    imshow("face", image);
}
