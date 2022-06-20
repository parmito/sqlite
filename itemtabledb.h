#ifndef ITEMTABLEDB_H
#define ITEMTABLEDB_H

#include <QDebug>
#include <QFont>
#include <QBrush>
#include <QTimer>
#include <QTime>
#include <QAbstractItemModel>

class ItemTableDB : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit ItemTableDB(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Add data:
    /*bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool insertColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;*/

    // Remove data:
    /*bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool removeColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;*/

    void timerHit();

private:
    QTimer *timer;
};

#endif // ITEMTABLEDB_H
