#pragma once

#include <QObject>
#include <QDateTime>
#include <QSqlDatabase>

//#include <complexinterface.h>
class ComplexInterface;

#include <data.h>

using Day = QVector<Data*>;

class Record : public QObject
{
    Q_OBJECT
private:
    quint64 id;
    QDate date;
    quint64 complex_id;
    ComplexInterface *complex;
    Day data;
    Record(quint64 id, QDate date, Day data, QObject *parent = nullptr);
public:
    static Record *createRecord(Day data, quint64 complex_id, QDate *date=Q_NULLPTR);
    static QVector<Record> *getRecords(quint64 complex_id=0, QDate *date=Q_NULLPTR);

    Record(quint64 id, QObject *parent = nullptr);

};

