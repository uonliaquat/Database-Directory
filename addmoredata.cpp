#include "addmoredata.h"
#include "ui_addmoredata.h"
#include "mainwindow.h"
#include "filehandling.cpp"
#include "addmoredataclass.cpp"
#include <sstream>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "mainwindow.h"
#include <QDebug>
#include "hashtable.cpp"
#include <QCloseEvent>
#include <QPixmap>



int no_of_coloumns;
FileHandling filehandling;
string selectedTableName;
string * coloumn_names;
QString data_to_add_q;
string ** data_ROWS_COLOUMNS;
int rows;

AddMoreData::AddMoreData(QWidget *parent):
    QWidget(parent),
    ui(new Ui::AddMoreData)
{


    ui->setupUi(this);
//    selectedTableName = filehandling.ReadSelectedTableName();
//    no_of_coloumns = countNoOfColoumns(selectedTableName);
    string tableName = getTableName(selectedTableName);
    string row = filehandling.ReadTableRow(tableName);
    coloumn_names = getColoumnsNames(row, no_of_coloumns);

    QPixmap pix("/Users/apple/Desktop/Qt\ Projects/DataStructures_Project/img/add_data.png");
    int w = ui->addDialog_logo->width();
    int h = ui->addDialog_logo->height();
    ui->addDialog_logo->setPixmap(pix.scaled(w,h, Qt::KeepAspectRatio));
}

AddMoreData::~AddMoreData()
{
    delete ui;
}


string AddMoreData::getTableName(string str){
    string TABLE_NAME;
    for(long i = 0; i < str.length(); i++){
        if(str[i] != ' '){
            TABLE_NAME = TABLE_NAME + str[i];
        }
        else{
            break;
        }
    }
    return TABLE_NAME;
}

int AddMoreData::countNoOfColoumns(string row){
    bool check  = false;
    string noOfColoumns_str;
    for(long i = 0; i < row.length(); i++){
        if(row[i-1] == ' ' || check){
            noOfColoumns_str = row[i] + noOfColoumns_str;
            check = true;
        }
    }
    stringstream geek(noOfColoumns_str);
    int x = 0;
    geek >> x;
    return x;
}


string AddMoreData:: setTableName(string value){
    table_name = value;
}


string * AddMoreData::getColoumnsNames(string str, int noOfColoumns){
//    string coloumn;
//    string * coloumns_names = new string[noOfColoumns];
//    int j = 0;
//    for(int i = 0; i < str.length() + 1; i++){
//        if(str[i] !=  ' '){
//            coloumn = coloumn + str[i];
//        }
//        else{
//            coloumns_names[j] = coloumn;
//            coloumn = "";
//            j++;
//        }
//    }
//    coloumns_names[j] = coloumn;
//    return coloumns_names;
}

void AddMoreData::on_pushButton_clicked()
{
    qApp->processEvents();
    MainWindow * main;
    string selectedTableName = main->getClickedTableName();

    QString entries_q = ui->lineEdit->text();
    string entries_s = entries_q.toUtf8().constData();
    stringstream geek(entries_s);
    geek >> rows;


    string * coloumnData = main->getHashTable()->getColoumnData(selectedTableName);
    int no_of_coloumns = main->getHashTable()->getNoOfColoumns(selectedTableName);
    for(int i = 0; i < no_of_coloumns; i++){
        QString str = QString::fromStdString(coloumnData[i]);
        qDebug() << str;
    }

    //Making Table View
    QStringList coloumns;
    QString string_q = QString::fromStdString("ID");
    coloumns << string_q;
    for(int i = 0; i < no_of_coloumns; i++){
      QString string_q = QString::fromStdString(coloumnData[i]);
      coloumns << string_q;
    }
    ui->tableWidget->setColumnCount(no_of_coloumns);
    ui->tableWidget->setHorizontalHeaderLabels(coloumns);
    for(int i = 0; i < rows; i++){
         ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    }
}


void AddMoreData::on_add_data_clicked()
{
    MainWindow * main;
    string selectedTableName = main->getClickedTableName();
    int no_of_coloumns = main->getNoOfColoumns(selectedTableName);

    data_ROWS_COLOUMNS = new string*[rows];
    for(int i = 0; i < rows; ++i){
        data_ROWS_COLOUMNS[i] = new string[no_of_coloumns];
    }

    QAbstractItemModel* model = ui->tableWidget->model();
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < no_of_coloumns; j++){
            QModelIndex idx = model->index(i, j);
            data_to_add_q = model->data(idx).toString();
            string str = data_to_add_q.toUtf8().constData();
            data_ROWS_COLOUMNS[i][j] = str;
        }
    }

    for(int i = 0; i < rows; i++){
        main->getHashTable()->insert(selectedTableName,data_ROWS_COLOUMNS[i],no_of_coloumns);
    }

   QMessageBox::information(this, "Message","\nData added successfully!");
}


int AddMoreData::key(string str){
    int key = 0;
    for(int i = 0; i < str.length(); i++){
        key = (str[i] * i) + key;
    }
    key = key % 10000;
    return key;
}


void AddMoreData::on_pushButton_2_clicked()
{
       ui->tableWidget->clear();
    //   for(int i = 0; i < rows; i++){
    //    ui->tableWidget->removeRow(i);
    //   }
    //   for(int i = 0; i <=ui->tableWidget->columnCount(); i++){
    //       ui->tableWidget->removeColumn(i);
    //   }
       while (ui->tableWidget->rowCount() > 0)
       {
           ui->tableWidget->removeRow(0);
       }
       while (ui->tableWidget->columnCount() > 0)
       {
           ui->tableWidget->removeColumn(0);
       }
}
