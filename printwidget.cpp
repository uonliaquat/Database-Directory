#include "printwidget.h"
#include "ui_printwidget.h"
#include "filehandling.cpp"
#include <QPixmap>

PrintWidget::PrintWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PrintWidget)
{
    ui->setupUi(this);
    QPixmap pix("/Users/apple/Desktop/Qt\ Projects/DataStructures_Project/img/print.png");
    int w = ui->printDialog_logo->width();
    int h = ui->printDialog_logo->height();
    ui->printDialog_logo->setPixmap(pix.scaled(w,h, Qt::KeepAspectRatio));


}

PrintWidget::~PrintWidget()
{
    delete ui;
}

void PrintWidget::on_comboBox_print_activated(int index)
{
   qApp->processEvents();
   MainWindow * main;
   QString table = ui->comboBox_print->currentText();
   string table_name = table.toUtf8().constData();

   int noOfColoumns = main->getHashTable()->getNoOfColoumns(table_name);
   int noOfEntries = main->getHashTable()->getNoOFEntries(table_name);
   string * coloumn = main->getHashTable()->getColoumnData(table_name);

    QStringList coloumns;
    ui->tableWidget->setColumnCount(noOfColoumns);
    ui->tableWidget->horizontalHeader()->setVisible(false);
    ui->tableWidget->setHorizontalHeaderLabels(coloumns);
    ui->tableWidget->setRowCount(noOfEntries+1);

    QString coloumn_q = QString::fromStdString("Id");
    ui->tableWidget->setItem(0,0, new QTableWidgetItem(coloumn_q));

    for(int i = 0 ; i< noOfColoumns-1; i++){
        QString coloumn_q = QString::fromStdString(coloumn[i]);
        ui->tableWidget->setItem(0,i+1, new QTableWidgetItem(coloumn_q));
    }

     string ** row = new string*[noOfEntries];
     for(int i = 0; i < noOfEntries; i++){
         row[i] = new string[noOfColoumns];
     }
     int currentIndex = 0;
     main->getHashTable()->getRowData(table_name, row, noOfColoumns, noOfEntries, &currentIndex);


    for(int i = 0; i < noOfEntries; i++){
        for(int j = 0; j < noOfColoumns; j++){
            QString row_q = QString::fromStdString(row[i][j]);
            ui->tableWidget->setItem(i+1,j, new QTableWidgetItem(row_q));
        }
    }

}

int PrintWidget::key(string str){
    int key = 0;
    for(int i = 0; i < str.length(); i++){
        key = (str[i] * i) + key;
    }
    key = key % 1000;
    return key;
}

void PrintWidget::on_pushButton_clicked()
{
    qApp->processEvents();
    if(ui->comboBox_print->count() != 0){
        ui->comboBox_print->clear();
    }
    MainWindow * main;
    foreach(QWidget * widget, QApplication::topLevelWidgets()) {
      if(widget->objectName() == "MainWindow"){
        main = dynamic_cast<MainWindow*>(widget);
        break;
      }
    }
    string * tables = main->getTableNames();
    int noOfTables = main->getNoOfTables();
    for(int i = 0; i < noOfTables; i++){
        QString table_name = QString::fromStdString(tables[i]);
        ui->comboBox_print->addItem(table_name);
    }

}
