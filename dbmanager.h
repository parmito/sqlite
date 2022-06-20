#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QString>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QStringList>
#include <QDateTime>

#define DATABASE "dbSqlite.db"
#define TABLE "itemTable"

class DBManager
{
public:
    DBManager(const QString& path);
    bool addItem(const QString& item,float price,const QString& local);
    bool addItem(const QString& item,const QString price,const QString& local);
    QList<QString> getItemList(void);
    QList<QString> getPriceList(void);
    QList<QString> getLocalList(void);
    QList<QString> getDateList(void);
    QString getLastField(QString& field );
    bool clearDB(void);
private:    
    QSqlDatabase m_db;
    QList<QString> m_listItem;
    QList<QString> m_listPrice;
    QList<QString> m_listLocal;
    QList<QString> m_listDate;
};

#endif // DBMANAGER_H
