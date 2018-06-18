#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <updatewidget.h>
#include <deletewidget.h>
#include <searchwidget.h>
#include <printwidget.h>
#include <addmoredata.h>
#include "hashtable.cpp"
#include <string>
#include <QApplication>
#include <QLabel>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    string getClickedTableName();
    string * getTableNames();
    QLabel qLabel;

private slots:
    void on_get_coloumns_button_clicked();

    void on_create_table_clicked();


    void on_comboBox_activated(int index);


    void on_ADD_BTN_clicked();

    void on_PRINT_BTN_clicked();

    void on_UPDATE_BTN_clicked();

    void on_DELETE_BTN_clicked();

    void on_SEARCH_BTN_clicked();

    void on_SAVE_BTN_clicked();


private:
    Ui::MainWindow *ui;
    DeleteWidget delete_widget;
    UpdateWidget update_widget;
    SearchWidget search_widget;
    PrintWidget print_widget;
    AddMoreData addMoreData;
    string * coloumnNames;
    string * coloumnValues;


public:

  HashTable * getHashTable();
  int getNoOfColoumns(string table_name);
  int getNoOfTables();
  void closeEvent (QCloseEvent *event);


};

#endif // MAINWINDOW_H
