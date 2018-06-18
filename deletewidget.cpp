#include "deletewidget.h"
#include "ui_deletewidget.h"
#include <iostream>
#include "mainwindow.h"


using namespace std;
DeleteWidget::DeleteWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeleteWidget)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setRowCount(5);


}

DeleteWidget::~DeleteWidget()
{
    delete ui;
}

void DeleteWidget::on_tableWidget_cellActivated(int row, int column)
{

}

void DeleteWidget::on_tableWidget_cellDoubleClicked(int row, int column)
{
    QString str;
    str = ui->tableWidget->item(row, column)->text();
    ui->label->setText(str);
}

void DeleteWidget::on_delete_enter_clicked()
{
//    qApp->processEvents();
//    string table_name = ui->delete_table_name->text().toStdString();
//    string id_s = ui->delete_id->text().toStdString();

//   MainWindow * mainWindow;
//   foreach(QWidget * widget, QApplication::topLevelWidgets()) {
//     if(widget->objectName() == "MainWindow"){
//       mainWindow = dynamic_cast<MainWindow*>(widget);
//       break;
//     }
//   }
//   mainWindow->getHashTable()->delete_data(table_name, id_s);
}
