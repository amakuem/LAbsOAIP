#include "mydata.h"

mydata::mydata() {}

void mydata::set(QStandardItemModel *model, QModelIndex &index)
{
    model->setData(index, dates);
}

void mydata::get(QString string)
{
    dates = string;
}

QString mydata::ret()
{
    return dates;
}
