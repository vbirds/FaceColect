#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QString>
#include <QFile>
#include <QTextStream>
#include "facedetec.h"
#include "facerecognize.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void videodec();
    void photodetec();
    void Saveface();

    void FaceCollect();

    void Trainxml();
    void FaceRec();


private:
    Ui::MainWindow *ui;
    facedetec *face;
    facerecognize *rec;
    QString   faceCollectPath;

};

#endif // MAINWINDOW_H
