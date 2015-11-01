#include "connection.h"
#include <QDebug>

Connection::Connection()
{
    this->InitDB("QMYSQL");
}

Connection::~Connection()
{
    this->myDB->close();
}

void Connection::InitDB(const QString dBType)
{
    if(dBType.isEmpty())
    {
        qDebug() << "func void Connection::InitDB() err check if(dBType.isEmpty())";
        return;
    }

    this->__dBType = dBType;
}

bool Connection::OpenDB(const QString hostName, const int port, const QString dBName,
                        const QString userName, const QString passWd)
{

    if(hostName.isEmpty() || dBName.isEmpty()
        || userName.isEmpty() || passWd.isEmpty())
    {
        qDebug() << "func bool Connection::OpenDB() check if(paratms.isEmpty())";
        return false;
    }

    this->myDB->setHostName(hostName);
    this->myDB->setPort(port);
    this->myDB->setDatabaseName(dBName);
    this->myDB->setUserName(userName);
    this->myDB->setPassword(passWd);

    if(this->myDB->open())
    {
        return true;
    } else {
        return false;
    }
}

