#include "itemtabledb.h"

ItemTableDB::ItemTableDB(QObject *parent)
    : QAbstractItemModel(parent)
{

}

QVariant ItemTableDB::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!

    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return QString("first");
        case 1:
            return QString("second");
        case 2:
            return QString("third");
        }
    }
    return QVariant();

}

QModelIndex ItemTableDB::index(int row, int column, const QModelIndex &parent) const
{
    // FIXME: Implement me!
}

QModelIndex ItemTableDB::parent(const QModelIndex &index) const
{
    // FIXME: Implement me!
}

int ItemTableDB::rowCount(const QModelIndex &parent) const
{
    /*if (!parent.isValid())
        return 0;*/

    return 2;

    // FIXME: Implement me!
}

int ItemTableDB::columnCount(const QModelIndex &parent) const
{
    /*if (!parent.isValid())
        return 0;*/

    return 4;
    // FIXME: Implement me!
}

QVariant ItemTableDB::data(const QModelIndex &index, int role) const
{
/*    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();*/


    if (role == Qt::DisplayRole) {
        return QString("Row%1, Column%2")
            .arg(index.row() + 1)
            .arg(index.column() +1);
    }
    return QVariant();

}

void ItemTableDB::timerHit()
{
    //we identify the top left cell
    QModelIndex topLeft = createIndex(0,0);
    //emit a signal to make the view reread identified data
    emit dataChanged(topLeft, topLeft, {Qt::DisplayRole});
}

/*
bool ItemTableDB::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endInsertRows();
    return true;
}

bool ItemTableDB::insertColumns(int column, int count, const QModelIndex &parent)
{
    beginInsertColumns(parent, column, column + count - 1);
    // FIXME: Implement me!
    endInsertColumns();
    return true;
}

bool ItemTableDB::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endRemoveRows();
    return true;
}

bool ItemTableDB::removeColumns(int column, int count, const QModelIndex &parent)
{
    beginRemoveColumns(parent, column, column + count - 1);
    // FIXME: Implement me!
    endRemoveColumns();
    return true;
}
*/
