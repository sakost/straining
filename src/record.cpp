/*
 * Copyright © 2020 by sakost
 *
 * This file is part of STraining, a Qt-based application for simplify trainings.
 *
 * STraining is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "record.h"

#include <QSqlQuery>
#include <QVariant>
#include <QSqlRecord>
#include <QDebug>
#include <QDate>
#include <QTime>

#include "complexinterface.h"

Record::Record(quint64 id,  QObject *parent) : QObject(parent)
{
    QSqlQuery query;
    query.prepare("SELECT count, relax_seconds, type, `date`, `time`, complex_id FROM `record` WHERE id=? LIMIT 1;");
    query.bindValue(0, QVariant(id));
    qDebug() << "executing query to database: " << query.lastQuery();
    query.exec();
    if(query.size() < 1){
        qWarning() << QString("record with id %1 was not found").arg(id);
        query.finish();
        return;
    }
    this->id = id;
    if(query.first()){
        QSqlRecord rec = query.record();
        this->count = query.value(rec.indexOf("count")).toUInt();
        this->relax_seconds = query.value(rec.indexOf("relax_seconds")).toUInt();
        this->type = query.value(rec.indexOf("type")).toString();
        this->date= query.value(rec.indexOf("date")).toDate();
        this->time = query.value(rec.indexOf("time")).toTime();
        this->complex = new ComplexInterface(query.value(rec.indexOf("complex_id")).toInt());
        query.finish();
    }else{
        qWarning() << QString("error while selecting record with id %1").arg(id);
    }
}

Record::Record(quint64 id, quint64 count, quint64 relax_seconds, QString type, QDate date, QTime time, quint64 complex_id, QObject *parent) : QObject(parent){
    this->id = id;
    this->count = count;
    this->relax_seconds = relax_seconds;
    this->type = type;
    this->date = date;
    this->time = time;
    this->complex_id = complex_id;

    this->complex = ComplexInterface::getComplex(this->complex_id);
}

Record* Record::createRecord(quint64 complex_id, quint64 count, quint64 relax_seconds, QString type, QDate *date, QTime *time){
    if(date == Q_NULLPTR){
        date = new QDate;
        *date = QDate::currentDate();
    }
    if(time == Q_NULLPTR){
        time = new QTime;
        *time = QTime::currentTime();
    }
    QSqlQuery query;

    query.prepare("INSERT INTO record (count, relax_seconds, type, `date`, `time`, complex_id) VALUES (?, ?, ?, ?, ?, ?);");

    query.bindValue(0, count);
    query.bindValue(1, relax_seconds);
    query.bindValue(2, type);
    query.bindValue(3, date->toString());
    query.bindValue(4, time->toString());
    query.bindValue(5, complex_id);
    qDebug() << "executing query to database: " << query.lastQuery();
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
    if(query.first()){
        QSqlRecord rec = query.record();
        id = query.value(rec.indexOf("id")).toUInt();

        Record *record = new Record(id, count, relax_seconds, type, *date, *time, complex_id);

        return record;
    } else{
        qCritical("something went VERY wrong...");
        return Q_NULLPTR;
    }
}
