#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSql>

class Connection
{
public:
    Connection();
    ~Connection();

    void InitDB(const QString dBType);

    bool OpenDB(const QString hostName, const int port,
                const QString dBName, const QString userName,
                const QString passWd
                );

private:
    QSqlDatabase *myDB;

    QString     __dBType;
    QString     __dBName;


/*
    QSqlDatabase *myDB;

    QString __dBType;
    QString __dBName;
*/

/*
bool    OpenDb(QString hostName, int port,QString dataBaseName,
               QString userName, QString passWord);
*/
};

#endif // CONNECTION_H
