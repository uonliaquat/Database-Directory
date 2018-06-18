#ifndef DELETEWIDGET_H
#define DELETEWIDGET_H

#include <QWidget>

namespace Ui {
class DeleteWidget;
}

class DeleteWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DeleteWidget(QWidget *parent = 0);
    ~DeleteWidget();


private slots:


    void on_tableWidget_cellActivated(int row, int column);

    void on_tableWidget_cellDoubleClicked(int row, int column);

    void on_delete_enter_clicked();

private:
    Ui::DeleteWidget *ui;
};

#endif // DELETEWIDGET_H
