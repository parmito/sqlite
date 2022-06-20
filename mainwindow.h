#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardPaths>
#include <QScreen>
#include <QMessageBox>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QQuickItem>
#include <QSqlTableModel>
#include "CustomQSqlTableModel.h"
#include "dbmanager.h"
#include "itemtabledb.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_m_toolButton_Adicionar_clicked();

    void on_m_toolButton_AdicionarEscolher_clicked();

    void on_m_pushButton_Filtrar_clicked();

private:
    Ui::MainWindow *ui;
    /* Also present are two methods that form
     * the model and appearance TableView
     * */
    CustomQSqlTableModel  *model;
    void setupModel(const QString &tableName, const QStringList &headers);
    void createUI(void);
    void InserirDadosDB(void);
    void InserirDadosDB(QString strItem, QString strLocal, QString strPreco);
    template<typename TItem> QList<TItem> LerDadosDB();
    template<typename TItem> QList<TItem>RemoveDuplicatesItemList(void);
    template<typename TItem> QList<TItem>RemoveDuplicatesPriceList(void);
    template<typename TItem> QList<TItem>RemoveDuplicatesLocalList(void);
    DBManager *db;
};
#endif // MAINWINDOW_H
