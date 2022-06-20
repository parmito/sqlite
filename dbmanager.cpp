#include "dbmanager.h"

DBManager::DBManager(const QString& path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path + DATABASE);

    if (!m_db.open())
    {
        qDebug() << "Error: connection with database failed";
        qWarning() << "ERROR: " << m_db.lastError();
    }
    else
    {
        qDebug() << "Database: connection ok";

        if(!m_db.tables().contains(QLatin1String("item")))
        {
            qDebug() << "Table does not exists yet. Please create!";
            QSqlQuery query("CREATE TABLE " TABLE " (id INTEGER PRIMARY KEY, item TEXT, price TEXT, date TEXT, local TEXT)");
            if(!query.isActive())
            {
                qWarning() << "ERROR: " << query.lastError().text();
            }
        }
        else
        {
            qDebug() << "Table already exists!";
        }
    }
}

bool DBManager::addItem(const QString& item,float price,const QString& local)
{
    bool success = false;
    /* you should check if args are ok first...*/

    QDateTime now = QDateTime::currentDateTime();
    QString sql_datetime_format = "dd-MM-yyyy";
    QString strSqlDateTime = now.toString(sql_datetime_format);

    QSqlQuery query;



    query.prepare("INSERT INTO itemTable (item,price,date,local) "
                  "VALUES (:item,:price,:date,:local)");
    query.bindValue(":item",item);
    query.bindValue(":price",price);
    query.bindValue(":date", strSqlDateTime);
    query.bindValue(":local",local);
    if(query.exec())
    {
        success = true;
    }
    else
    {
        qDebug() << "addItem error:"
                 << query.lastError();
    }

    return success;
}

bool DBManager::addItem(const QString& item,const QString price,const QString& local)
{
    bool success = false;
    /* you should check if args are ok first...*/

    QDateTime now = QDateTime::currentDateTime();
    QString sql_datetime_format = "dd-MM-yyyy";
    QString strSqlDateTime = now.toString(sql_datetime_format);

    QSqlQuery query;



    query.prepare("INSERT INTO itemTable (item,price,date,local) "
                  "VALUES (:item,:price,:date,:local)");
    query.bindValue(":item",item);
    query.bindValue(":price",price);
    query.bindValue(":date", strSqlDateTime);
    query.bindValue(":local",local);
    if(query.exec())
    {
        success = true;
    }
    else
    {
        qDebug() << "addItem error:"
                 << query.lastError();
    }

    return success;
}


#if 0
QList<QString> DBManager::getField(QString& field )
{
    QString query = "SELECT * FROM itemTable";
    QSqlQuery SqlQuery = QSqlQuery( m_db );
    SqlQuery.exec( query );

    while (SqlQuery.next())
    {
        int field_idx   = SqlQuery.record().indexOf(field);
        QString strItem = SqlQuery.record().value( field_idx ).toString();            
        m_list.append(strItem);
        qDebug() << strItem;
    };
    return(m_list);
}
#endif

QList<QString> DBManager::getItemList(void)
{
    QString query = "SELECT * FROM itemTable";
    QSqlQuery SqlQuery = QSqlQuery( m_db );
    SqlQuery.exec( query );

    m_listItem.clear();
    while (SqlQuery.next())
    {
        int field_idx   = SqlQuery.record().indexOf("item");
        QString strItem = SqlQuery.record().value( field_idx ).toString();
        m_listItem.append(strItem);
        qDebug() << strItem;
    };
    return(m_listItem);

}

QList<QString> DBManager::getPriceList(void)
{
    QString query = "SELECT * FROM itemTable";
    QSqlQuery SqlQuery = QSqlQuery( m_db );
    SqlQuery.exec( query );

    m_listPrice.clear();
    while (SqlQuery.next())
    {
        int field_idx   = SqlQuery.record().indexOf("price");
        QString strItem = SqlQuery.record().value( field_idx ).toString();
        m_listPrice.append(strItem);
        qDebug() << strItem;
    };
    return(m_listPrice);
}


QList<QString> DBManager::getLocalList(void)
{
    QString query = "SELECT * FROM itemTable";
    QSqlQuery SqlQuery = QSqlQuery( m_db );
    SqlQuery.exec( query );

    m_listLocal.clear();
    while (SqlQuery.next())
    {
        int field_idx   = SqlQuery.record().indexOf("local");
        QString strLocal = SqlQuery.record().value( field_idx ).toString();
        m_listLocal.append(strLocal);
        qDebug() << strLocal;
    };
    return(m_listLocal);
}

QList<QString> DBManager::getDateList(void)
{
    QString query = "SELECT * FROM itemTable";
    QSqlQuery SqlQuery = QSqlQuery( m_db );
    SqlQuery.exec( query );

    m_listDate.clear();
    while (SqlQuery.next())
    {
        int field_idx   = SqlQuery.record().indexOf("date");
        QString strDate = SqlQuery.record().value( field_idx ).toString();
        m_listDate.append(strDate);
        qDebug() << strDate;
    };
    return(m_listLocal);

}

QString DBManager::getLastField(QString& field )
{
    QString strItem;
    QString query = "SELECT * FROM itemTable";
    QSqlQuery SqlQuery = QSqlQuery( m_db );
    SqlQuery.exec( query );

    while (SqlQuery.next())
    {
        int field_idx   = SqlQuery.record().indexOf(field);
        strItem = SqlQuery.record().value( field_idx ).toString();
    };
    qDebug() << strItem;

    return(strItem);
}

bool DBManager::clearDB(void)
{
    bool boReturn = false;

    QString query = "DELETE FROM itemTable";
    QSqlQuery SqlQuery = QSqlQuery( m_db );
    SqlQuery.exec( query );
    boReturn = true;

    return(boReturn);
}
