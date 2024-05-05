#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QPushButton>
#include <QTimer>
#include <QEventLoop>
#include <QElapsedTimer>
#include <QMessageBox>

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
protected:
    void paintEvent(QPaintEvent*);

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    int m_size = 400;
    int* m_data = nullptr;
    int* tempData = nullptr;


    void merge(int l, int m, int r);
    void mergeSort(int l, int r);
    void heapify(int n, int i);
    void heapSort(int n);
    int partition(int low, int high);
    void quickSort(int low, int high);
    void delay(int time);
    void chooseSort();
};
#endif // MAINWINDOW_H
