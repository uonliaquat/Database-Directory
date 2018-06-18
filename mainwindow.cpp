#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "filehandling.cpp"
#include "linkedlist.cpp"

#include <iostream>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <string>
#include <sstream>
#include <QLineEdit>
#include <QMessageBox>
#include <QPixmap>
#include "hashtable.cpp"
#include <QLabel>
#include <sstream>


QLineEdit * lineEdit;
QLineEdit * lineEdit1;
string table_name;
LinkedList linkedlist;
QVBoxLayout * lay;
QHBoxLayout * Hlay;
string selected_table;
HashTable hashtable;
int _noOfColoumns;
string * getTables;
int _noOfTables;

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    setFixedHeight(570);
    setFixedWidth(800);
    this->setWindowTitle("Local Database");

    QPixmap pix("/Users/apple/Desktop/Qt\ Projects/DataStructures_Project/img/add_data.png");
    QPixmap pix1("/Users/apple/Desktop/Qt\ Projects/DataStructures_Project/img/update_data.png");
    QPixmap pix2("/Users/apple/Desktop/Qt\ Projects/DataStructures_Project/img/deletedata.png");
    QPixmap pix3("/Users/apple/Desktop/Qt\ Projects/DataStructures_Project/img/search.png");
    QPixmap pix4("/Users/apple/Desktop/Qt\ Projects/DataStructures_Project/img/savedata.png");
    QPixmap pix5("/Users/apple/Desktop/Qt\ Projects/DataStructures_Project/img/print.png");
    QIcon ButtonIcon(pix);
    ui->ADD_BTN->setIcon(ButtonIcon);
    QIcon ButtonIcon1(pix1);
    ui->UPDATE_BTN->setIcon(ButtonIcon1);
    QIcon ButtonIcon2(pix2);
    ui->DELETE_BTN->setIcon(ButtonIcon2);
    QIcon ButtonIcon3(pix3);
    ui->SEARCH_BTN->setIcon(ButtonIcon3);
    QIcon ButtonIcon4(pix4);
    ui->SAVE_BTN->setIcon(ButtonIcon4);
    QIcon ButtonIcon5(pix5);
    ui->PRINT_BTN->setIcon(ButtonIcon5);


    //setting loogo
   QPixmap pix6("//Users/apple/Downloads/algorithems.png");
   int w = ui->logo->width();
   int h = ui->logo->height();
   ui->logo->setPixmap(pix6.scaled(w,h, Qt::KeepAspectRatio));
    //Add Widget Pages
    ui->stackedWidget->insertWidget(1, &delete_widget);
    ui->stackedWidget->insertWidget(2, &update_widget);
    ui->stackedWidget->insertWidget(3, &search_widget);
    ui->stackedWidget->insertWidget(4, &print_widget);
    ui->stackedWidget->insertWidget(5, &addMoreData);






    //RETIEVE List
    FileHandling file;
    string ** list_R = file.readList();

    for(int i = 0; i < file.readTableCount(); i++){
        string * data;
        int noOfColoumns;
        QString str = QString::fromStdString(list_R[i][0]);
        ui->comboBox->addItem(str);
        stringstream geek(list_R[i][1]);
        geek >> noOfColoumns;
        data = new string[noOfColoumns];
        for(int j = 2; j < noOfColoumns+2; j++){
            data[j-2] = list_R[i][j];
            QString str = QString::fromStdString(data[j-2]);
            qDebug()<<str;
        }
        hashtable.insertColoumns(list_R[i][0],noOfColoumns,data);
        string ** table_data = file.readTable(list_R[i][0], noOfColoumns+1);
        int noOfRows = file.readRowCount(list_R[i][0]);
        string * newString = new string[noOfColoumns+1];
        for(int k = 0; k < noOfRows; k++){
            for(int l = 0; l < noOfColoumns+1; l++){
                newString[l] = table_data[k][l];
            }
            hashtable.BST_insert(list_R[i][0],newString, noOfColoumns+1);
        }
    }


}

MainWindow::~MainWindow()
{
    delete ui;

}


void MainWindow::on_get_coloumns_button_clicked()
{

    qApp->processEvents();

    QString coloumnsq = ui->noOfColoumns_lineEdit->text();
    string coloumns = coloumnsq.toUtf8().constData();
    stringstream geek(coloumns);
    geek >> _noOfColoumns;
    coloumnNames = new string[_noOfColoumns];
    QString tableName = ui->table_name->text();
    string table_name = tableName.toUtf8().constData();
    bool checkValue = false;
    for(int i = 0 ; i < ui->comboBox->count(); i++){
        string str = ui->comboBox->itemText(i).toStdString();
        if(table_name == str){
            checkValue = true;
        }
    }
    if(!checkValue){
        lay = new QVBoxLayout(this);
        for(int i = 0; i < _noOfColoumns; i++){
            Hlay = new QHBoxLayout(this);
            QLabel * index = new QLabel(QString::number(i+1));
            QLabel * label = new QLabel("   Coloumn Name");
            lineEdit = new QLineEdit();
            Hlay->addWidget(index);
            Hlay->addWidget(label);
            Hlay->addWidget(lineEdit);
            lay->addLayout(Hlay);
        }
        ui->scrollContents->setLayout(lay);
    }
    else{
        QMessageBox::information(this, "Error","\nTable Already Exists!");
    }
}

void MainWindow::on_create_table_clicked()
{

    int j = 0;
    QList<QLineEdit*> LINE_EDITS = ui->addTable_scrollArea->findChildren<QLineEdit *>();
    for(int i = 0; i < _noOfColoumns ;i++){
      QString coloum_Name = LINE_EDITS.at(i)->text();
      coloumnNames[i] = coloum_Name.toUtf8().constData();
      j++;
    }
    QString tableName = ui->table_name->text();
    string table_name = tableName.toUtf8().constData();
    ui->comboBox->addItem(tableName);
    hashtable.insertColoumns(table_name, _noOfColoumns, coloumnNames);
    QMessageBox::information(this, "Message","\nTable created successfully!");

    FileHandling file;
    string * coloumnData = hashtable.getColoumnData(table_name);
    file.writeList(table_name, _noOfColoumns, coloumnData);


    QList<QVBoxLayout *> vlayout = ui->addTable_scrollArea->findChildren<QVBoxLayout *>();
    QList<QHBoxLayout *> hlayout = ui->addTable_scrollArea->findChildren<QHBoxLayout *>();
    QList<QLabel *> label = ui->addTable_scrollArea->findChildren<QLabel *>();
    QList<QLineEdit *> lineEdit = ui->addTable_scrollArea->findChildren<QLineEdit *>();

    for (QVBoxLayout * i: vlayout) {
         i->deleteLater();
    }
    for (QHBoxLayout * j: hlayout) {
         j->deleteLater();
    }
    for (QLabel * k: label) {
         k->deleteLater();
    }
    for (QLineEdit * l: lineEdit) {
         l->deleteLater();
    }



}
void MainWindow::on_comboBox_activated(int index)
{
    qApp->processEvents();
    QString string_q = ui->comboBox->currentText();
    selected_table = string_q.toUtf8().constData();
    ui->stackedWidget->setCurrentIndex(5);
}

string MainWindow::getClickedTableName(){
    return selected_table;
}

HashTable * MainWindow::getHashTable(){
    return &hashtable;
}

string * MainWindow::getTableNames(){
    getTables = new string[ui->comboBox->count()];
    _noOfTables = ui->comboBox->count();
    for(int i = 0 ; i < ui->comboBox->count(); i++){
        getTables[i] = ui->comboBox->itemText(i).toStdString();
    }
    return getTables;
}

int MainWindow::getNoOfColoumns(string table_name){
    return hashtable.getNoOfColoumns(table_name);
}
int MainWindow::getNoOfTables(){
    _noOfTables = ui->comboBox->count();
    return _noOfTables;
}


void MainWindow::on_ADD_BTN_clicked()
{
      qApp->processEvents();
     ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_PRINT_BTN_clicked()
{
       qApp->processEvents();
    getTables = new string[ui->comboBox->count()];
    _noOfTables = ui->comboBox->count();
    for(int i = 0 ; i < ui->comboBox->count(); i++){
        getTables[i] = ui->comboBox->itemText(i).toStdString();
    }
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_UPDATE_BTN_clicked()
{
       qApp->processEvents();
      ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_DELETE_BTN_clicked()
{
       qApp->processEvents();
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_SEARCH_BTN_clicked()
{
    qApp->processEvents();
     ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_SAVE_BTN_clicked()
{

    FileHandling file;
    string * tables = new string[ui->comboBox->count()];
    int * no_of_coloumns = new int[ui->comboBox->count()];
    for(int i = 0 ; i < ui->comboBox->count(); i++){
        tables[i] = ui->comboBox->itemText(i).toStdString();
    }
    for(int i = 0; i < ui->comboBox->count(); i++){
        no_of_coloumns[i] = hashtable.getNoOfColoumns(tables[i]);
    }




    for(int i = 0; i < ui->comboBox->count(); i++){
      int noOfEntries = hashtable.getNoOFEntries(tables[i]);
      string ** row = new string*[noOfEntries];
      for(int j = 0; j < noOfEntries; j++){
          row[j] = new string[no_of_coloumns[i]];
      }
      int currentIndex = 0;
      hashtable.getPreOrder(tables[i], row, no_of_coloumns[i], noOfEntries, &currentIndex);
      file.writeTable(tables[i], row, noOfEntries, no_of_coloumns[i]);
    }

    QMessageBox::information(this,"Dialog","\nData saved successfully");

}

void MainWindow::closeEvent (QCloseEvent *event)
{

    FileHandling file;
    string * tables = new string[ui->comboBox->count()];
    int * no_of_coloumns = new int[ui->comboBox->count()];
    for(int i = 0 ; i < ui->comboBox->count(); i++){
        tables[i] = ui->comboBox->itemText(i).toStdString();
    }
    for(int i = 0; i < ui->comboBox->count(); i++){
        no_of_coloumns[i] = hashtable.getNoOfColoumns(tables[i]);
    }




    for(int i = 0; i < ui->comboBox->count(); i++){
      int noOfEntries = hashtable.getNoOFEntries(tables[i]);
      string ** row = new string*[noOfEntries];
      for(int j = 0; j < noOfEntries; j++){
          row[j] = new string[no_of_coloumns[i]];
      }
      int currentIndex = 0;
      hashtable.getPreOrder(tables[i], row, no_of_coloumns[i], noOfEntries, &currentIndex);
      file.writeTable(tables[i], row, noOfEntries, no_of_coloumns[i]);
    }

}
