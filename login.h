#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();
    void  Login_Main();

private slots:
    void on_login_ToolButton_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
