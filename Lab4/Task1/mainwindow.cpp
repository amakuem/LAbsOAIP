#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_data = new int[m_size];
    tempData = new int[m_size];
    for (int i = 0; i < m_size; ++i) {
        m_data[i] = rand() % 200;
        tempData[i] = m_data[i];
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent*) {
    QPainter painter(this);

    painter.drawRect(20, 20, 600, 350);
    painter.setBrush(Qt::blue);

    if (m_size != 0) {
        int w = 600 / m_size;
        for(int i = 0; i < m_size; ++i) {
            painter.drawRect(20 + i * w, 370, w, -m_data[i]);
        }
    }
}

void MainWindow::merge(int l, int m, int r)
{

    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    for (i = 0; i < n1; i++)
        tempData[i] = m_data[l + i];
    for (j = 0; j < n2; j++)
        tempData[n1 + j] = m_data[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (tempData[i] <= tempData[n1 + j]) {
            m_data[k] = tempData[i];
            i++;
        } else {
            m_data[k] = tempData[n1 + j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        m_data[k] = tempData[i];
        i++;
        k++;
    }

    while (j < n2) {
        m_data[k] = tempData[n1 + j];
        j++;
        k++;
    }
    QTimer::singleShot(100, this, [=] { update(); });
    //update();
}

void MainWindow::mergeSort(int l, int r)
{
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(l, m);
        mergeSort(m + 1, r);

        //QTimer::singleShot(1000, this, [=] { merge(l, m, r); });
        merge(l, m, r);
    }
}

void MainWindow::heapify(int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && m_data[left] > m_data[largest])
        largest = left;

    if (right < n && m_data[right] > m_data[largest])
        largest = right;

    if (largest != i) {
        std::swap(m_data[i], m_data[largest]);
        heapify(n, largest);
    }
    update();
}

void MainWindow::heapSort(int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(n, i);

    for (int i = n - 1; i >= 0; i--) {
        std::swap(m_data[0], m_data[i]);
        heapify(i, 0);
    }
}

int MainWindow::partition(int low, int high)
{
    int pivot = m_data[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (m_data[j] < pivot) {
            i++;
            std::swap(m_data[i], m_data[j]);
        }
    }
    std::swap(m_data[i + 1], m_data[high]);
    update();
    return (i + 1);
}

void MainWindow::quickSort(int low, int high)
{
    if (low < high) {
        int pi = partition(low, high);

        quickSort(low, pi - 1);
        quickSort(pi + 1, high);
    }
}

void MainWindow::on_pushButton_clicked()
{
        mergeSort(0, m_size - 1);
}

