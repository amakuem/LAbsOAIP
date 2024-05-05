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
        m_data[i] = rand() % 340;
        tempData[i] = m_data[i];
    }

    isSorted = false;
    isNumberGood = false;

    connect(ui->lineEdit, &QLineEdit::returnPressed, this, &MainWindow::getNumber);
    connect(ui->lineEdit, &QLineEdit::cursorPositionChanged, this, &MainWindow::lineChanged);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent*) {
    QPainter painter(this);

    painter.drawRect(219, 40, 800, 500);
    painter.setBrush(Qt::red);

    if (m_size != 0) {
        int w = 800 / m_size;
        for(int i = 0; i < m_size; ++i) {
            //painter.drawRect(20 + i * w, 370, w, -m_data[i]);
            painter.drawRect(219 + i * w, 540, w, -m_data[i]);
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

            delay(0.5);
            update();
        } else {
            m_data[k] = tempData[n1 + j];
            j++;

            delay(0.5);
            update();
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

}

void MainWindow::mergeSort(int l, int r)
{
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(l, m);
        mergeSort(m + 1, r);

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

        delay(0.5);
        update();

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

            delay(0.5);
            update();
        }
    }
    std::swap(m_data[i + 1], m_data[high]);

    delay(0.5);
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
    if(!isSorted)
    {
        ui->pushButton->setDisabled(true);
        ui->lineEdit->setDisabled(true);

        if(ui->comboBox->currentIndex() == 0)
        {
            isSorted = true;
            mergeSort(0, m_size - 1);
        }
        else if(ui->comboBox->currentIndex() == 1)
        {
            isSorted = true;
            quickSort(0, m_size - 1);
        }
        else if(ui->comboBox->currentIndex() == 2)
        {
            isSorted = true;
            heapSort(m_size);
        }

        ui->pushButton->setEnabled(true);
        ui->lineEdit->setEnabled(true);
    }
}

void MainWindow::delay(int time)
{
    QEventLoop loop;
    QTimer::singleShot(time, &loop, &QEventLoop::quit);
    loop.exec();
}

void MainWindow::getNumber()
{
    bool ok;
    numberForBinarySearch = ui->lineEdit->text().toInt(&ok);
    if(!ok)
    {
        isNumberGood = false;
        QMessageBox::warning(this, "Ошибка", "Введенное значение не является числом");
    }
    else
    {
        isNumberGood = true;
        ui->lineEdit->setReadOnly(true);
    }
    setIndexOfNumber();
}

void MainWindow::lineChanged()
{
    ui->lineEdit->setReadOnly(false);
}

int MainWindow::binarySearch()
{
    int left = 0;
    int right = m_size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (m_data[mid] == numberForBinarySearch)
            return mid;
        if (m_data[mid] < numberForBinarySearch)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;  // если число не найдено
}

void MainWindow::setIndexOfNumber()
{
    if(!isSorted && !isNumberGood)
    {
        QMessageBox::warning(this, "Ошибка", "Массив должен быть отсортирован");
        return ;
    }
    int index = binarySearch();
    ui->label_3->setText(QString::number(index));
}

