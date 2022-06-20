#include "mainwindow.h"
#include "ui_mainwindow.h"

#define  QT_DEBUG

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /* Findout Screen Size*/
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    int height = screenGeometry.height();
    int width = screenGeometry.width();

    qDebug() << "Width" << width;
    qDebug() << "Height" << height;

    /* Create Database*/
    /*QString path = QStandardPaths::writableLocation( QStandardPaths::StandardLocation::DataLocation);
    db = new DBManager(path);*/

    QFile dfile("assets:/db/dbSqlite.db");
    if (dfile.exists())
    {
        dfile.copy("./dbSqlite.db");
        QFile::setPermissions("./dbSqlite.db",QFile::WriteOwner | QFile::ReadOwner);
    }
    db = new DBManager("./");


    QList<QString> strListResult;
    strListResult = RemoveDuplicatesItemList<QString>();


    for(int i = 0; i < strListResult.size();i++)
    {        
        ui->m_ComboBox_Item->addItem(strListResult.at(i));
        ui->m_ComboBoxItem_HL->addItem(strListResult.at(i));
    }

    strListResult.empty();
    strListResult = RemoveDuplicatesLocalList<QString>();
    for(int i = 0; i < strListResult.size();i++)
    {
        ui->m_ComboBox_Local->addItem(strListResult.at(i));
        ui->m_ComboBoxLocal_HL->addItem(strListResult.at(i));
    }

    strListResult.empty();
    strListResult = RemoveDuplicatesPriceList<QString>();
    for(int i = 0; i < strListResult.size();i++)
    {
        ui->m_ComboBox_Price->addItem(strListResult.at(i));
        ui->m_ComboBoxPrice_HL->addItem(strListResult.at(i));
    }

    QDateTime now = QDateTime::currentDateTime();
    QString datetime_format = "dd-MM-yyyy";
    QString strDateTime = now.toString(datetime_format);

    ui->m_label_DiaMesAno->setText(strDateTime);
    ui->m_label_DiaMesAno_Escolher->setText(strDateTime);

    this->setupModel(TABLE,
                     QStringList() << ("id  ")
                                   << ("Produtos        ")
                                   << ("Preços")
                                   << ("Dia                 ")
                                   << ("Local")
                     );

    /* Initialize the appearance of a table with data
     * */
    this->createUI();


    qDebug() << QLocale().name();
    ui->m_tableView_Today->setFrameStyle(QFrame::StyledPanel);
    ui->m_tableView_Today->setAutoFillBackground(true);
    /*ui->m_tableView_Today->setStyleSheet(   "QTableView{"
                                            "background: url(:/rc/android/assets/img/fruits.png);"
                                            "}");*/

    QDate today = QDate::currentDate();
    ui->m_dateEdit_HL->setDate(today);
}

template<typename TItem> QList<TItem>MainWindow::RemoveDuplicatesItemList(void)
{
    QList<QString> strListResult;
    strListResult = db->getItemList();

    QVector<QString> vectListResult;
    vectListResult = strListResult.toVector();

    std::sort( vectListResult.begin(), vectListResult.end() );
    /* Remove Duplicates*/
    vectListResult.erase( std::unique(vectListResult.begin(), vectListResult.end() ), vectListResult.end() );
    strListResult = vectListResult.toList();

    return(strListResult);
}

template<typename TItem> QList<TItem>MainWindow::RemoveDuplicatesPriceList(void)
{
    QList<QString> strListResult;
    strListResult = db->getPriceList();

    QVector<QString> vectListResult;
    vectListResult = strListResult.toVector();

    std::sort( vectListResult.begin(), vectListResult.end() );
    /* Remove Duplicates*/
    vectListResult.erase( std::unique(vectListResult.begin(), vectListResult.end() ), vectListResult.end() );
    strListResult = vectListResult.toList();

    return(strListResult);
}

template<typename TItem> QList<TItem>MainWindow::RemoveDuplicatesLocalList(void)
{
    QList<QString> strListResult;
    strListResult = db->getLocalList();

    QVector<QString> vectListResult;
    vectListResult = strListResult.toVector();
    std::sort( vectListResult.begin(), vectListResult.end() );
    /* Remove Duplicates*/
    vectListResult.erase( std::unique(vectListResult.begin(), vectListResult.end() ), vectListResult.end() );
    strListResult = vectListResult.toList();

    return(strListResult);
}


/* Method for initializing data representation model
 * */
void MainWindow::setupModel(const QString &tableName, const QStringList &headers)
{
    /* Initializes the data model representation with the installation name
     * in the database table, on which will be accessed in the table
     * */
    model = new CustomQSqlTableModel(this);
    model->setTable(tableName);

    /* Set the columns names in a table with sorted data
     * */
    for(int i = 0, j = 0; i < model->columnCount(); i++, j++){
        model->setHeaderData(i,Qt::Horizontal,headers[j]);
    }
    // Set Sort Ascending steering column data
    model->setSort(0,Qt::AscendingOrder);
}

void MainWindow::createUI()
{
    ui->m_tableView_Today->setModel(model);     // We set the model on the TableView
    ui->m_tableView_Today->setColumnHidden(0, true);    // Hide the column id Records
    // Allow the selection of lines
    ui->m_tableView_Today->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Set selection mode, only one row in table
    ui->m_tableView_Today->setSelectionMode(QAbstractItemView::SingleSelection);
    // Set the size of the columns by content
    ui->m_tableView_Today->resizeColumnsToContents();
    ui->m_tableView_Today->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->m_tableView_Today->horizontalHeader()->setStretchLastSection(true);

    ui->m_tableView_Today->setAlternatingRowColors(false);
    ui->m_tableView_Today->horizontalHeader()->setStyleSheet("QHeaderView{"
                                         "background-color: rgb(250, 115, 115);"
                                         "font-size: 40px;"
                                         "font-weight: bold;"
                                         "}");

    ui->m_tableView_Today->setStyleSheet("QTableView{"
                                         "background-color: rgb(250, 250, 115);"
                                         "font-weight: bold;"
                                         "alternate-background-color: rgb(250, 115, 115);"
                                         "font-size: 30px;"
                                         "}");

    /* Filtering SQLite data */
    QDateTime now = QDateTime::currentDateTime();
    QString sql_datetime_format = "dd-MM-yyyy";
    QString strSqlDateTime = now.toString(sql_datetime_format);
    QString strFilter("date=\'"+strSqlDateTime+"\'");

    model->setFilter(strFilter);
    model->select(); /* Fetches the data from the table */
}

void MainWindow::InserirDadosDB(QString strItem, QString strLocal, QString strPreco)
{
    bool boResult = false;    
    bool ok = true;
    if(ok == true)
    {
        if((strItem.size() >0) && (strPreco.size() > 0) &&  (strLocal.size() > 0))
        {
            boResult = db->addItem(strItem,strPreco,strLocal);
            if(boResult == true){
                QMessageBox msgBox;
                msgBox.setText("Itens inseridos corretamente!");
                msgBox.setIcon(QMessageBox::Information);
                msgBox.setButtonText(QMessageBox::AcceptRole,"OK!");
                msgBox.exec();
            }
        }
        else
        {
            QMessageBox msgWarning;
            msgWarning.setText("Atenção!\nExistem campos vazios,\nou com caracteres desconhecidos");
            msgWarning.setIcon(QMessageBox::Warning);
            msgWarning.setWindowTitle("Erro");
            msgWarning.exec();
        }
    }
    else
    {
        QMessageBox msgWarning;
        msgWarning.setText("Atenção!\nEntre com um número");
        msgWarning.setIcon(QMessageBox::Warning);
        msgWarning.setWindowTitle("Erro");
        msgWarning.exec();
    }
}

void MainWindow::on_m_toolButton_Adicionar_clicked()
{
    QString strItem = ui->m_textEdit_Item->toPlainText();
    QString strLocal = ui->m_textEdit_Local->toPlainText();
    QString strPreco = ui->m_textEdit_Preco->toPlainText();

    this->InserirDadosDB((strItem.trimmed()).toLower(), (strLocal.trimmed()).toLower(), (strPreco.trimmed()).toLower());
    ui->m_textEdit_Item->clear();
    ui->m_textEdit_Preco->clear();
    ui->m_ComboBox_Item->clear();

    ui->m_ComboBoxItem_HL->clear();
    ui->m_ComboBoxLocal_HL->clear();
    ui->m_ComboBoxPrice_HL->clear();

    QList<QString> strListResult;

    strListResult = RemoveDuplicatesItemList<QString>();
    ui->m_ComboBox_Item->clear();
    for(int i = 0; i < strListResult.size();i++)
    {
        ui->m_ComboBox_Item->addItem(strListResult.at(i));
        ui->m_ComboBoxItem_HL->addItem(strListResult.at(i));
    }

    strListResult.clear();
    strListResult = RemoveDuplicatesLocalList<QString>();
    ui->m_ComboBox_Local->clear();
    for(int i = 0; i < strListResult.size();i++)
    {
        ui->m_ComboBox_Local->addItem(strListResult.at(i));
        ui->m_ComboBoxLocal_HL->addItem(strListResult.at(i));
    }

    strListResult.clear();
    strListResult = RemoveDuplicatesPriceList<QString>();
    ui->m_ComboBox_Price->clear();
    for(int i = 0; i < strListResult.size();i++)
    {
        ui->m_ComboBox_Price->addItem(strListResult.at(i));
        ui->m_ComboBoxPrice_HL->addItem(strListResult.at(i));
    }

    model->select(); /* Fetches the data from the table*/
}


void MainWindow::on_m_toolButton_AdicionarEscolher_clicked()
{
    QString strItem = ui->m_ComboBox_Item->currentText();
    QString strLocal = ui->m_ComboBox_Local->currentText();
    QString strPreco = ui->m_ComboBox_Price->currentText();

    this->InserirDadosDB((strItem.trimmed()).toLower(), (strLocal.trimmed()).toLower(), (strPreco.trimmed()).toLower());
    ui->m_textEdit_Item->clear();
    ui->m_textEdit_Preco->clear();

    ui->m_ComboBoxItem_HL->clear();
    ui->m_ComboBoxLocal_HL->clear();
    ui->m_ComboBoxPrice_HL->clear();

    QList<QString> strListResult;
    strListResult = RemoveDuplicatesItemList<QString>();
    ui->m_ComboBox_Item->clear();
    for(int i = 0; i < strListResult.size();i++)
    {
        ui->m_ComboBox_Item->addItem(strListResult.at(i));
        ui->m_ComboBoxItem_HL->addItem(strListResult.at(i));
    }

    strListResult.clear();
    strListResult = RemoveDuplicatesLocalList<QString>();
    ui->m_ComboBox_Local->clear();
    for(int i = 0; i < strListResult.size();i++)
    {
        ui->m_ComboBox_Local->addItem(strListResult.at(i));
        ui->m_ComboBoxLocal_HL->addItem(strListResult.at(i));
    }

    strListResult.clear();
    strListResult = RemoveDuplicatesPriceList<QString>();
    ui->m_ComboBox_Price->clear();
    for(int i = 0; i < strListResult.size();i++)
    {
        ui->m_ComboBox_Price->addItem(strListResult.at(i));
        ui->m_ComboBoxPrice_HL->addItem(strListResult.at(i));
    }

    model->select(); // Fetches the data from the table
}


MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_m_pushButton_Filtrar_clicked()
{
    std::map<QString,QString> qstrMapSqlFilter;
    QString strSqliteFilterClause;

    qstrMapSqlFilter.insert({"item",ui->m_ComboBoxItem_HL->currentText()});
    qstrMapSqlFilter.insert({"price",ui->m_ComboBoxPrice_HL->currentText()});
    qstrMapSqlFilter.insert({"local",ui->m_ComboBoxLocal_HL->currentText()});
    QString strDate = ui->m_dateEdit_HL->text();
    qstrMapSqlFilter.insert({"date",strDate});

    for (const auto& [key, value] : qstrMapSqlFilter)
    {
        qDebug()<< '[' << key << "] = " << value << "; ";
    }
    strSqliteFilterClause.append("date=\'"+qstrMapSqlFilter["date"]+"\'");
    strSqliteFilterClause.append(" AND " "item=\'"+qstrMapSqlFilter["item"]+"\'");
    strSqliteFilterClause.append(" AND " "local=\'"+qstrMapSqlFilter["local"]+"\'");

    float flMin = ui->m_ComboBoxPrice_HL->currentText().toFloat();
    flMin = (flMin*100)/100;
    QString qstrFloatMin =QString::number(flMin);

    strSqliteFilterClause.append(" AND price=" + qstrFloatMin);

    qDebug() << strSqliteFilterClause;

    model->setFilter(strSqliteFilterClause);   
    model->select(); /* Fetches the data from the table*/

    qstrMapSqlFilter.clear();

}

