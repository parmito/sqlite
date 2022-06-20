#include "CustomQSqlTableModel.h"
#include "qcolor.h"

CustomQSqlTableModel::CustomQSqlTableModel(QObject *parent)
    : QSqlTableModel(parent)
{       
}

QVariant CustomQSqlTableModel::data(const QModelIndex &index, int role=Qt::ForegroundRole) const
{
    QVariant value;

    //if (index.isValid()) {

        switch(role)
        {
            case Qt::ForegroundRole:
                value =  QVariant::fromValue(QColor(Qt::black));
                break;

            default:
                value = QSqlTableModel::data(index, role);
                if((role == Qt::DisplayRole) && (index.column()== 2))
                {
                    value = value.toString();
                }
                break;
        }


#if 0
        if (role < Qt::UserRole)
        {
            value = QSqlTableModel::data(index, role);
        }
        else
        {

            /*int columnIdx = role - Qt::UserRole - 1;
            QModelIndex modelIndex = this->index(index.row(), columnIdx);
            value = QSqlTableModel::data(modelIndex, Qt::ForegroundRole);*/
        }
#endif
    //}
    return value;
}
