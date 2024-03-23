#ifndef MYDATA_H
#define MYDATA_H

#include <QStandardItemModel>

class mydata
{
public:
    mydata();

    mydata NextDay();
    mydata PreviousDay();
    void set(QStandardItemModel *model, QModelIndex &index);
    int DaysTillYourBithday(mydata bithdaydate);
    int Duration (mydata date);
    void get(QString string);
    QString ret();
private:
    QString dates;
    mydata **moyaDates;
    int size;
};

#endif // MYDATA_H
