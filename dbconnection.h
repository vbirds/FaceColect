#ifndef DBCONNECTION
#define DBCONNECTION

#include <QSqlDatabase>
#include <QSqlError>
#include <QSql>

static bool InitDB()
{
    QSqlDatabase myDB = QSqlDatabase::addDatabase("QMYSQL");

    myDB.setHostName("localhost");
    myDB.setPort(3306);
    myDB.setDatabaseName("test");
    myDB.setUserName("root");
    myDB.setPassword("admin");

    if(!myDB.open())
    {
        return false;
    }

    return true;

}


#endif // DBCONNECTION

