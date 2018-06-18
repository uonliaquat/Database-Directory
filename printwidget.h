#ifndef PRINTWIDGET_H
#define PRINTWIDGET_H

#include <QWidget>
using namespace std;
namespace Ui {
class PrintWidget;
}

class PrintWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PrintWidget(QWidget *parent = 0);
    ~PrintWidget();

private slots:
    void on_comboBox_print_activated(int index);

    void on_pushButton_clicked();

private:
    Ui::PrintWidget *ui;

public:
    int key(string str);
};

#endif // PRINTWIDGET_H
