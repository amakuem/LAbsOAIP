#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "mydata.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void getInformation();

    void makeTable();

private:
    Ui::MainWindow *ui;
    QStandardItemModel *model;
    mydata **moyaDate;
    QString pathFile;
    QString moidates;
};
#endif // MAINWINDOW_H
