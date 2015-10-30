#include "mainwindow.h"
#include "login.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    Login sign;
    sign.show();
   if(sign.exec() == QDialog::Accepted)
   {
        w.show();
        return a.exec();
   }
  else
  {
       return 0;
  }


}
