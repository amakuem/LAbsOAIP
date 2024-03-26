#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    listView = new QListView();
    model = new QStringListModel(this);

    QStringList l;
    l << "Процессор" << "Видеокарта" << "Оперативная память" << "Материнская плата" << "Жесткий диск(HDD)" << "Твердотелый накопитель(SSD)" << "Блок питания" << "Корпус";
    model->setStringList(l);


    ui->listView->setModel(model);
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

    pathFile = QFileDialog::getOpenFileName(0, "Открыть файл","/home/skibidi-dop", "*txt");
    //ui->label->setText(pathFile);
    openfile();
}


void MainWindow::on_pushButton_2_clicked()
{
    QModelIndex index = ui->listView->currentIndex();
    QString text = index.data(Qt::DisplayRole).toString();

    ui->label->setText(text);
}

void MainWindow::openfile()
{
    information = "";
    QFile file(pathFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug("Не удалось открыть файл для чтения, сосите");
        return;
    }
    QTextStream in(&file);

    while(!in.atEnd())
    {
        information += in.readLine();
        information += '\n';
    }
    file.close();
    makeBase();
}

void MainWindow::makeBase()
{
    model->removeRows(0, model->rowCount());

    QString temp = "";
    QString text = "";
    int schet = 0;
    kolvo = 0;
    int schetProbel = 5;
    bool param = false;
    for(int i = 0; i < information.length(); i++)
    {
        if(information[i] == ' ' && (information[i + 1] == ' ' || information[i + 1] == '\n'))
        {
            continue;
        }

        if(information[i] == ':')
        {
            param = true;

        }
        else if(information[i] == ';')
        {
            param = false;

        }
        if(!param && information[i] == ' ')
        {
            schet++;
        }

        if(information[i] == '\n')
        {
            if(schet == schetProbel)
            {
                kolvo++;
                schet = 0;
                text += temp;
                temp = "";
            }
        }

        temp += information[i];
    }

    temp = "";
    schet = 1;
    int j = 0;

    components = new component *[kolvo];
    for(int i = 0; i < kolvo; i++)
    {
        components[i] = new component();
    }

    for(int i = 0; i < text.length(); i++)
    {
        if(i != 0 && information[i] == ' ' && information[i - 1] == ';')
        {
            schet++;
            param = false;
            continue;
        }
        if(information[i] == ':')
        {
            param = true;
            temp = "";
            continue;
        }
        else if(information[i] == ';')
        {

            components[j]->getParametrs(temp);
            temp = "";
            continue;
        }
        if(param)
        {
            temp += text[i];
            continue;
        }
        if(text[i] == ' ' && schet == 1 && j < kolvo)
        {
            components[j]->getType(temp);
            schet++;
            temp = "";
            continue;
        }
        else if(text[i] == ' ' && schet == 2 && j < kolvo)
        {
            components[j]->getFirm(temp);
            schet++;
            temp = "";
            continue;
        }
        else if(text[i] == ' ' && schet == 3 && j < kolvo)
        {
            components[j]->getCompModel(temp);
            schet++;
            temp = "";
            continue;
        }
        else if(text[i] == ' ' && schet == 5 && j < kolvo)
        {
            temp.chop(1);
            int x = temp.toInt();
            components[j]->getPrice(x);
            schet++;
            temp = "";
            continue;
        }
        else if(text[i] == '\n' && j < kolvo)
        {
            if(temp == "есть")
            {
                components[j]->getAvailability(true);
            }
            else
            {
                components[j]->getAvailability(false);
            }
            j++;
            schet = 1;
            temp = "";
            continue;
        }
        temp += text[i];
    }

    QStringList l;
    for(int i = 0; i < kolvo; i++)
    {
        l << components[i]->retType();
    }
    model->setStringList(l);


    ui->listView->setModel(model);
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);

}
