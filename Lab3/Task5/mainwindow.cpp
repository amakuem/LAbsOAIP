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
    count(dir, filesCount, subFoldersCount);

    ui -> label_2 -> setText(QString::number(subFoldersCount));
    ui -> label_4 -> setText(QString::number(filesCount));
}

void MainWindow::count(QDir& dir, int& filesCount, int& subFoldersCount)
{
    QFileInfoList files = dir.entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
    for (QFileInfo& file : files) {
        if (file.isDir()) {
            subFoldersCount++;
            QDir dir_2(file.filePath());
            count(dir_2, filesCount, subFoldersCount);
        }
        else if (file.isFile()) {
            filesCount++;
        }
    }
}
