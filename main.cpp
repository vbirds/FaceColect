#include "mainwindow.h"
#include "login.h"
#include "dbconnection.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if(!InitDB())
    {
        return 0;
    }

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
\
}
