#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <algorithm>

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

    void calculateMedians();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QVector<int> a = {1, 5, 1, 4, 5, 6, 2, 1, 3, 4, 4, 4, 5, 7};
    QVector<int> temp;
    QVector<int> b;


};
#endif // MAINWINDOW_H
