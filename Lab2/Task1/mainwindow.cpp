#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    model = new QStandardItemModel(this);
    ui->tableView->setModel(model);


    ui->tableView->setSelectionMode(QAbstractItemView::NoSelection);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    model->setRowCount(10);
    model->setColumnCount(8);
    ui->tableView->horizontalHeader()->model()->setHeaderData(0, Qt::Horizontal, "Дата");
    ui->tableView->horizontalHeader()->model()->setHeaderData(1, Qt::Horizontal, "След. день");
    ui->tableView->horizontalHeader()->model()->setHeaderData(2, Qt::Horizontal, "Дата - След. дата");
    ui->tableView->horizontalHeader()->model()->setHeaderData(3, Qt::Horizontal, "Пред. день");
    ui->tableView->horizontalHeader()->model()->setHeaderData(4, Qt::Horizontal, "Тип года");
    ui->tableView->horizontalHeader()->model()->setHeaderData(5, Qt::Horizontal, "День недели");
    ui->tableView->horizontalHeader()->model()->setHeaderData(6, Qt::Horizontal, "Дата - д.р.");
    ui->tableView->horizontalHeader()->model()->setHeaderData(7, Qt::Horizontal, "Тек. дата - данной");

    //moyaDate->set(model, index);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    pathFile = QFileDialog::getOpenFileName(0, "Открыть файл","/home/skibidi-dop", "*txt");
    ui->label->setText(pathFile);
    getInformation();
}

void MainWindow::getInformation()
{
    moidates = "";
    QFile file(pathFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug("Не удалось открыть файл для чтения, сосите");
        return;
    }
    QTextStream in(&file);

    while(!in.atEnd())
    {
        moidates += in.readLine();
        moidates += ' ';
    }
    ui->label->setText(moidates);
    //moidates.;
    file.close();
    makeTable();
}

void MainWindow::makeTable()
{
    QString temp = "";
    bool chyslo = false;
    int kolvo = 0;
    for(int i = 0; i < moidates.length(); i++)
    {
        if(!chyslo && moidates[i] == ' ' && (moidates[i + 1] < 48 || moidates[i + 1] > 57))
        {
            continue;
        }

        if((moidates[i] >= 48 && moidates[i] <= 57) || (moidates[i] == '.' || moidates[i] == ',' || moidates[i] == '/'))
        {
            temp += moidates[i];
            chyslo = true;
        }
        else if(i != 0 && (moidates[i - 1]>= 48 && moidates[i - 1] <= 57) && moidates[i] == ' ' && (chyslo))
        {
            kolvo ++;
            temp += ' ';
        }
        else
        {
            chyslo = false;
        }
    }

    moyaDate = new mydata*[kolvo];
    for(long i = 0; i < kolvo; i++)
    {
        moyaDate[i] = new mydata();
    }

    int j = 0;
    QString string;
    for(int i = 0; i < temp.length(); i++)
    {
        if(temp[i] != ' ')
        {
            string += temp[i];
        }
        else if(temp[i] == ' ' && j < kolvo)
        {
            moyaDate[j]->get(string);
            j++;
            string = "";

        }
    }

    for(int i = 0; i < kolvo; i++)
    {
        QModelIndex index = model->index(i, 0);

        moyaDate[i]->set(model, index);
    }

    ui->label_2->setText(moyaDate[0]->ret());
    ui->label_3->setText(moyaDate[1]->ret());
}
