#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString mainDir = QFileDialog::getExistingDirectory(this, "Открыть", "../../");
    QDir dir(mainDir);
    int subFoldersCount = 0;
    int filesCount = 0;
    countDirectory(dir, subFoldersCount);
    countFile(dir, filesCount);

    ui -> label_2 -> setText(QString::number(subFoldersCount));
    ui -> label_4 -> setText(QString::number(filesCount));
}

void MainWindow::countDirectory(QDir &dir, int &subFoldersCount)
{
    QFileInfoList files = dir.entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
    for (QFileInfo& file : files) {
        if (file.isDir()) {
            subFoldersCount++;
            QDir dir_2(file.filePath());
            countDirectory(dir_2, subFoldersCount);
        }
    }
}

void MainWindow::countFile(QDir &dir, int& filesCount)
{
    QFileInfoList files = dir.entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
    for (QFileInfo& file : files) {
        if (file.isFile())
        {
            filesCount++;
            QDir dir_2(file.filePath());
            countFile(dir_2, filesCount);
        }
    }
}

