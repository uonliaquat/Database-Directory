#ifndef ADDMOREDATA_H
#define ADDMOREDATA_H

#include <QWidget>
#include <string>

using namespace std;
namespace Ui {
class AddMoreData;
}

class AddMoreData : public QWidget
{
    Q_OBJECT

public:
    explicit AddMoreData(QWidget *parent = 0);
    ~AddMoreData();
     string getTableName(string str);
     string setTableName(string value);
     int countNoOfColoumns(string value);
     string * getColoumnsNames(string str, int noOfColoumns);



private:
    Ui::AddMoreData *ui;
public:
    string table_name;
private slots:
    void on_pushButton_clicked();
    void on_add_data_clicked();
    int key(string str);
    void on_pushButton_2_clicked();
};

#endif // ADDMOREDATA_H
