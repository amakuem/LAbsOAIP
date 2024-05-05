#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //calculateMedians();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::calculateMedians()
{
    int j = 0;
    int sum  = 0;
    for(int i = 0; i < a.size(); i++)
    {
        //count++;
        if(temp.size() != 3)
        {
            temp.push_back(a[i]);
            j++;
        }
        if(temp.size() == 3 || i == a.size() - 1)
        {
            j = 0;
            std::sort(temp.begin(), temp.end());

            if(temp.size() == 3)
            {
                b.push_back(temp[1]);

                temp.clear();
                //temp.push_back(a[i]);
            }
            else
            {
                for(int m = 0; m < temp.size(); m++)
                {
                    sum += temp[m];
                }
                b.push_back(sum/temp.size());

                sum = 0;
                temp.clear();
                //temp.push_back(a[i]);
            }
        }
    }


}

void MainWindow::on_pushButton_clicked()
{
    calculateMedians();
    QString string = "";
    for (int i = 0; i < b.size(); i++) {
        string += QString::number(b[i]);
        string += ", ";
    }
    string.chop(2);
    ui->label->setText(string);
}

