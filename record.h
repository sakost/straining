#pragma once

#define ALL_COMPLEXES 0

#include <QObject>
#include <QDateTime>
#include <QSqlDatabase>

class ComplexInterface;

class Record : public QObject
{
    Q_OBJECT
private:
    quint64 id;
    quint64 count;
    quint64 relax_seconds;
    QString type;
    QDate date;
    QTime time;
    quint64 complex_id;
    ComplexInterface *complex;
    Record(quint64 id, quint64 count, quint64 relax_seconds, QString type, QDate date, QTime time, quint64 complex_id, QObject *parent = nullptr);
public:
    static Record *createRecord(quint64 complex_id, quint64 count=0, quint64 relax_seconds=0, QString type="", QDate *date=Q_NULLPTR, QTime *time=Q_NULLPTR);
    static QVector<Record> *getRecords(quint64 complex_id=ALL_COMPLEXES, QDate *date=Q_NULLPTR);

    Record(quint64 id, QObject *parent = nullptr);

};

