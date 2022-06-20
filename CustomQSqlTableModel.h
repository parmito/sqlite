#ifndef CUSTOMQSQLTABLEMODEL_H
#define CUSTOMQSQLTABLEMODEL_H

#include <QSqlTableModel>

class CustomQSqlTableModel : public QSqlTableModel
{

public:
    explicit CustomQSqlTableModel(QObject *parent = nullptr);
    QVariant data(const QModelIndex &index, int role) const;  
};

#endif // CUSTOMQSQLTABLEMODEL_H
