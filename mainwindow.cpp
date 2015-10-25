#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->face = new facedetec();
    this->rec = new facerecognize();

    QObject::connect(ui->Start_toolButton, SIGNAL(clicked(bool)), this, SLOT(videodec()));
    QObject::connect(ui->Photo_toolButton, SIGNAL(clicked(bool)), this, SLOT(photodetec()));
    QObject::connect(ui->Save_toolButton, SIGNAL(clicked(bool)), this, SLOT(Saveface()));
    QObject::connect(ui->Collect_toolButton, SIGNAL(clicked(bool)), this, SLOT(FaceCollect()));

    QObject::connect(ui->Train_toolButton, SIGNAL(clicked(bool)), this, SLOT(Trainxml()));
    QObject::connect(ui->Recface_toolButton,SIGNAL(clicked(bool)), this, SLOT(FaceRec()));
}

MainWindow::~MainWindow()
{
    delete ui;
    if(this->face)
    {
        delete(this->face);
    }
}

void MainWindow::videodec()
{
    if(this->face)
    {
        this->face->VideoDetecFace(0);
    }
}

void MainWindow::photodetec()
{
    QString path = QFileDialog::getOpenFileName(this,tr("Open File"),
                                                QDir::currentPath(),
                                                tr("Image Files (*.png *.jpg *.bmp *.pgm)")
                                                );
    this->face->Detecface(path);
}

void MainWindow::Saveface()
{
    int rec = 0;
    QString path = "D:/QtMsvcProjects/face/02";
    rec = this->face->SaveFace(path);

    QMessageBox::information(NULL, "success", "Save success");
}

void MainWindow::FaceCollect()
{
    QString path = "D:/QtMsvcProjects/face/03";

    this->face->VideoCollectInit(path, true);
}

void MainWindow::Trainxml()
{
    int ret;
    QString path = "D:/QtProject/att_faces/at.txt";
    ret = this->rec->Learn(path);

    if(ret == 0)
      {
          QMessageBox::information(NULL,"Informaition", "Train Succcess");
      }
      else
      {
          QMessageBox::information(NULL,"Informaition", "Train failed");
      }
}

void MainWindow::FaceRec()
{
    this->rec->VideoRecognize(0);
}





