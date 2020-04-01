#include "record.h"

#include <QSqlQuery>
#include <QVariant>
#include <QSqlRecord>
#include <QDebug>
#include <QDate>

#include <complexinterface.h>

Record::Record(quint64 id,  QObject *parent) : QObject(parent)
{
    QSqlQuery query;
    query.prepare("SELECT complex_id, `date` FROM `record` WHERE id=? LIMIT 1;");
    query.bindValue(0, QVariant(id));
    qDebug() << "executing query to database: " << query.lastQuery();
    query.exec();
    if(query.size() < 1){
        qWarning() << QString("record with id %1 was not found").arg(id);
        query.finish();
        return;
    }
    this->id = id;
    query.next();
    this->date= query.value(1).toDate();
    this->complex = new ComplexInterface(query.value(0).toInt());
    query.finish();
}

Record::Record(quint64 id, QDate date, Day data, QObject *parent): QObject(parent){
    this->id = id;
    this->date= date;
    this->data = data;
}

Record* Record::createRecord(Day data, quint64 complex_id, QDate *date){
    if(date == Q_NULLPTR){
        date = new QDate;
        *date = QDate::currentDate();
    }
    QSqlQuery query;

    query.prepare("INSERT INTO record (complex_id, `date`) VALUES (?, ?)");

    query.bindValue(0, QVariant(complex_id));
    query.bindValue(1, date->toString());
    if(!query.exec()){
        qWarning() << QString("can't insert record");
        return Q_NULLPTR;
    }
    query.finish();

    quint64 id;

    if(!query.exec("SELECT id FROM record ORDER BY id DESC LIMIT 1;")){
        qWarning() << "error while getting id of last record";
        return Q_NULLPTR;
    }
    id = query.value(0).toUInt();

    Record *record = new Record(id, *date, data); // warn: maybe compilation error

    for(auto &set: data){
        set->toDb(id);
    }

    return record;
}
