#include "login.h"
#include "ui_login.h"
#include <QSqlQuery>
#include <QDebug>

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    ui->userName_LineEdit->setFocus();
    ui->passWd_LineEdit->setEchoMode(QLineEdit::Password);
}

Login::~Login()
{
    delete ui;
}

void Login::Login_Main()
{
    QString user = ui->userName_LineEdit->text().trimmed();
    QString passWd = ui->passWd_LineEdit->text().trimmed();

    if(passWd.isEmpty())
    {
        QMessageBox::information(this, tr("Please Input passWD"), tr("Please Input passWD before Loging"), QMessageBox::Ok);
        ui->passWd_LineEdit->setFocus();
        return;
    } else {
        QSqlQuery query;
        query.exec(QString("select A_PW from administrator where A_ID = %1").arg(user));

        if(query.next())
        {
            //QString pass = query.value(0).toString().trimmed();
            //qDebug() << pass;
            if(query.value(0).toString().trimmed() == passWd) {
                QDialog::accept();
            } else {
                QMessageBox::warning(this, tr("passwd error"),tr("please Input corrected passwd"),QMessageBox::Ok);
                ui->passWd_LineEdit->clear();
                ui->passWd_LineEdit->setFocus();
            }
        } else {
            QMessageBox::information(this, tr("Login"),tr("No user named this"),QMessageBox::Ok);
            ui->passWd_LineEdit->clear();
            ui->userName_LineEdit->setFocus();
        }
    }

    /*
        QSqlQuery query;
        query.exec("select pwd from password");
        query.next();
        if (query.value(0).toString() == ui->pwdLineEdit->text()) {
            QDialog::accept();
        } else {
            QMessageBox::warning(this, tr("密码错误"),
                                 tr("请输入正确的密码再登录！"), QMessageBox::Ok);
            ui->pwdLineEdit->clear();
            ui->pwdLineEdit->setFocus();
        }
    */
    /*
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
        //ui->userName_LineEdit->setFocus();
        return;
    }
    return;
    */
}

void Login::on_login_ToolButton_clicked()
{
    Login_Main();
}
