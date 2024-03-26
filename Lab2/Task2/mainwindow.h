#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QListView>
#include <QStringListModel>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include "component.h"

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

    void on_pushButton_2_clicked();

    void openfile();

    void makeBase();
private:
    Ui::MainWindow *ui;
    QListView *listView;
    QStringListModel *model;
    QStandardItemModel *model2;
    QString pathFile;
    QString information;
    component **components;
    int kolvo;
};
#endif // MAINWINDOW_H
