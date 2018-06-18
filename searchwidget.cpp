#include "searchwidget.h"
#include "ui_searchwidget.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <ctime>
#include <QApplication>
#include <QWindow>
#include <QPixmap>

using namespace std;

SearchWidget::SearchWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchWidget)
{
    ui->setupUi(this);
    QPixmap pix("/Users/apple/Desktop/Qt\ Projects/DataStructures_Project/img/search.png");
    int w = ui->searchDialog_logo->width();
    int h = ui->searchDialog_logo->height();
    ui->searchDialog_logo->setPixmap(pix.scaled(w,h, Qt::KeepAspectRatio));
}

SearchWidget::~SearchWidget()
{
    delete ui;
}

void SearchWidget::on_pushButton_clicked()
{
    qApp->processEvents();
    if(ui->table_name->text().isEmpty()){
          QMessageBox::information(NULL,"Result","Please Enter the Table Name first!");
          return;
    }
    else if(ui->id->text().isEmpty()){
          QMessageBox::information(NULL,"Result","Please Enter Id first!");
          return;
    }

        MainWindow * main;
        QString table_name_q = ui->table_name->text();
        string table_name = table_name_q.toUtf8().constData();
        QString id_q = ui->id->text();
        string id = id_q.toUtf8().constData();
        int no_of_coloumns = main->getNoOfColoumns(table_name);
        string * coloumnData = main->getHashTable()->getColoumnData(table_name);

        HashTable * hashtable = main->getHashTable();
        clock_t begin = clock();
        string * searchResult = hashtable->search(table_name, id);
        clock_t end = clock();
        double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
        QString time_sec = QString::number(elapsed_secs);
        ui->lcdNumber->display(time_sec);
        if(searchResult[0] == "NO_TABLE"){
            QMessageBox::information(NULL,"Result","No such Table Exists");
        }
        else if(searchResult[0] == "NO_ID"){
            QMessageBox::information(NULL,"Result","No such ID Exists");
        }
        else{
            //Making Table View
            ui->tableWidget->setColumnCount(2);
            ui->tableWidget->setRowCount(no_of_coloumns);

            QStringList coloumns;
            QString string_q = QString::fromStdString("Id");
            ui->tableWidget->setItem(0,0, new QTableWidgetItem(string_q));
            for(int i = 0; i < no_of_coloumns - 1; i++){
                QString string_q = QString::fromStdString(coloumnData[i]);
                ui->tableWidget->setItem(i+1,0, new QTableWidgetItem(string_q));
            }
            for(int i = 0; i <=no_of_coloumns; i++){
              QString string_q = QString::fromStdString(searchResult[i]);
              ui->tableWidget->setItem(i,1, new QTableWidgetItem(string_q));
            }
        }
    }

void SearchWidget::UpdateLabel(const QString text)
{
    ui->lcdNumber->display(text);
}

void SearchWidget::on_pushButton_2_clicked()
{
     qApp->processEvents();
     if(ui->wholeSearch_LE->text().isEmpty()){
        QMessageBox::information(NULL,"Result","Please Enter Id first!");
     }
    MainWindow * mainWindow;
    foreach(QWidget * widget, QApplication::topLevelWidgets()) {
      if(widget->objectName() == "MainWindow"){
        mainWindow = dynamic_cast<MainWindow*>(widget);
        break;
      }
    }
   HashTable * hashtable = mainWindow->getHashTable();
   bool check = false;
   int no_of_coloumns;
   string str = ui->wholeSearch_LE->text().toStdString();
   string * table_names = mainWindow->getTableNames();
   int no_of_tables = mainWindow->getNoOfTables();
   for(int i = 0; i < no_of_tables; i++){
      clock_t begin = clock();
      string * result = hashtable->search(table_names[i], str);
      clock_t end = clock();
      double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
      QString time_sec = QString::number(elapsed_secs);
        ui->lcdNumber->display(time_sec);
      string * coloumnData = hashtable->getColoumnData(table_names[i]);
      if(result[0] == str){
          check = true;
          no_of_coloumns = mainWindow->getNoOfColoumns(table_names[i]);
          //Making Table View
          ui->tableWidget->setColumnCount(2);
          ui->tableWidget->setRowCount(no_of_coloumns);

          QStringList coloumns;
          QString string_q = QString::fromStdString("Id");
          ui->tableWidget->setItem(0,0, new QTableWidgetItem(string_q));
          for(int i = 0; i < no_of_coloumns - 1; i++){
              QString string_q = QString::fromStdString(coloumnData[i]);
              ui->tableWidget->setItem(i+1,0, new QTableWidgetItem(string_q));
          }
          for(int i = 0; i <=no_of_coloumns; i++){
            QString string_q = QString::fromStdString(result[i]);
            ui->tableWidget->setItem(i,1, new QTableWidgetItem(string_q));
          }
      }
   }
   if(!check){
        QMessageBox::information(NULL,"Result","No such ID Exists");
   }
}
