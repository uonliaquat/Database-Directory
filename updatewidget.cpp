#include "updatewidget.h"
#include "ui_updatewidget.h"
#include "mainwindow.cpp"
#include <QPixmap>

UpdateWidget::UpdateWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UpdateWidget)
{
    ui->setupUi(this);
    QPixmap pix("//Users/apple/Desktop/Qt\ Projects/DataStructures_Project/img/update_data.png");
    int w = ui->updateDialog_logo->width();
    int h = ui->updateDialog_logo->height();
    ui->updateDialog_logo->setPixmap(pix.scaled(w,h, Qt::KeepAspectRatio));
}

UpdateWidget::~UpdateWidget()
{
    delete ui;
}

void UpdateWidget::on_pushButton_clicked()
{
    qApp->processEvents();

    if(ui->table_name_U->text().isEmpty()){
        QMessageBox::information(NULL,"Result","Please Enter Table Name first!");
        return;
    }
    else if(ui->id_U->text().isEmpty()){
        QMessageBox::information(NULL,"Result","Please Enter Id first!");
        return;
    }
    MainWindow * main;
    QString table_name_q = ui->table_name_U->text();
    string table_name = table_name_q.toUtf8().constData();
    QString id_q = ui->id_U->text();
    string id = id_q.toUtf8().constData();
    int no_of_coloumns = main->getNoOfColoumns(table_name);
    string * coloumnData = main->getHashTable()->getColoumnData(table_name);



    HashTable * hashtable = main->getHashTable();
    string * searchResult = hashtable->search(table_name, id);
    if(searchResult[0] == "NO_TABLE"){
        QMessageBox::information(NULL,"Result","No such Table Exists");
    }
    else if(searchResult[0] == "NO_ID"){
        QMessageBox::information(NULL,"Result","No such ID Exists");
    }
    else{
        //Making Table View
        ui->tableWidget_U->setColumnCount(2);
        ui->tableWidget_U->setRowCount(no_of_coloumns);

        QStringList coloumns;
        QString string_q = QString::fromStdString("Id");
        ui->tableWidget_U->setItem(0,0, new QTableWidgetItem(string_q));
        for(int i = 0; i < no_of_coloumns - 1; i++){
            QString string_q = QString::fromStdString(coloumnData[i]);
            ui->tableWidget_U->setItem(i+1,0, new QTableWidgetItem(string_q));
        }
        for(int i = 0; i <=no_of_coloumns; i++){
          QString string_q = QString::fromStdString(searchResult[i]);
          ui->tableWidget_U->setItem(i,1, new QTableWidgetItem(string_q));
        }
    }

}

void UpdateWidget::on_update_U_clicked()
{
    qApp->processEvents();
    MainWindow * main;
    QString table_name_q = ui->table_name_U->text();
    string table_name = table_name_q.toUtf8().constData();
    int no_of_coloumns = main->getNoOfColoumns(table_name);

    QString * string_q = new QString[no_of_coloumns];
    string * changed_data = new string[no_of_coloumns];
    for(int i = 0; i < no_of_coloumns; i++){
        string_q[i] = ui->tableWidget_U->item(i,1)->text();
    }
    for(int i = 0; i < no_of_coloumns; i++){
        changed_data[i] = string_q[i].toUtf8().constData();
    }
    clock_t begin = clock();
    main->getHashTable()->update(table_name, changed_data, changed_data[0], no_of_coloumns);
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    QString time_sec = QString::number(elapsed_secs);
    ui->lcdNumber->display(time_sec);
    QMessageBox::information(NULL,"Result","Data Updated Successfuly!");
}
