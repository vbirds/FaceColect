#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    ui->passWd_LineEdit->setEchoMode(QLineEdit::Password);
}

Login::~Login()
{
    delete ui;
}

void Login::Login_Main()
{
    QString user = ui->userName_LineEdit->text();
    QString passWd = ui->passWd_LineEdit->text();

    if(user == "admin" && passWd == "123")
    {
        accept();
    }
    else
    {
        QMessageBox::warning(this, tr("Warning"),
                             tr("user name or password err!"),
                             QMessageBox::Yes);

        ui->userName_LineEdit->clear();
        ui->passWd_LineEdit->clear();
        ui->userName_LineEdit->setFocus();
        return;
    }
    return;
}

void Login::on_login_ToolButton_clicked()
{
    Login_Main();
}
