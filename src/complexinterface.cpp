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

#include "complexinterface.h"

#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QDebug>


QSet<ComplexInterface*> *ComplexInterface::complexes = Q_NULLPTR;
const QString invalidName = "<NULL>";

QSet<ComplexInterface*>& ComplexInterface::getComplexes(){
    if(ComplexInterface::complexes == Q_NULLPTR){
        ComplexInterface::complexes = new QSet<ComplexInterface*>;
    }
    return *ComplexInterface::complexes;
}

ComplexInterface::ComplexInterface(quint64 id, const QString& uName, QObject *parent):QObject(parent){
    this->id=id;
    this->uName = uName;
}



bool ComplexInterface::registerComplex(ComplexInterface *ci){
    quint64 id;
    if((id = ComplexInterface::hasAlreadyComplex(ci->uName)) > 0){
        ci->id = id;
        ComplexInterface::getComplexes().insert(ci);
        qInfo() << QString("complex '%1' was already set up(id %2)").arg(ci->uName).arg(ci->id);
        return true;
    }
    QSqlQuery query;
    query.prepare("INSERT INTO complex (name) VALUES (?);");
    query.bindValue(0, ci->uName);
    qDebug() << "executing query to database: " << query.lastQuery();
    if(!query.exec()){
        qWarning() << "error while registering complex";
        return false;
    }
    query.finish();
    query.prepare("SELECT id FROM complex ORDER BY id DESC LIMIT 1;");
    qDebug() << "executing query to database: " << query.lastQuery();
    if(!query.exec()){
        qWarning() << "error while registering complex";
        return false;
    }
    if(query.first()){
        QSqlRecord record = query.record();
        ci->id = query.value(record.indexOf("id")).toUInt();
        query.finish();

        ComplexInterface::getComplexes().insert(ci);
        qInfo() << QString("registered complex '%1' with id %2").arg(ci->uName).arg(ci->id);
        return true;
    } else{
        qFatal("smth went VERY wrong...");
        return false;
    }
}

quint64 ComplexInterface::hasAlreadyComplex(const QString& name){
    QSqlQuery query;
    query.prepare("SELECT id FROM `complex` WHERE name=? LIMIT 1;");
    query.bindValue(0, name);
    if(!query.exec()){
        qWarning() << "error while querying complex";
        return 0;
    }
    if(query.first()){
        QSqlRecord record = query.record();
        return query.value(record.indexOf("id")).toUInt();
    } else{
        qInfo() << "complex hasn't exists yet";
        return 0;
    }
}

ComplexInterface* ComplexInterface::getComplex(quint64 id){
    QSqlQuery query;
    query.prepare("SELECT name FROM `complex` WHERE id=? LIMIT 1;");
    query.bindValue(0, id);
    qDebug() << "executing query to database: " << query.lastQuery();
    if(!query.exec()){
        qWarning() << "error while getting complex data";
        return Q_NULLPTR;
    }
    if(query.first()){
        QSqlRecord rec = query.record();
        ComplexInterface *res = new ComplexInterface(id, query.value(rec.indexOf("name")).toString());
        res->id = id;
        res->uName = query.value(0).toString();
        query.finish();
        return res;
    } else{
        qInfo() << QString("there is no complex with id %1").arg(id);
        return Q_NULLPTR;
    }
}

ComplexInterface* ComplexInterface::getComplex(const QString &name){
    QSqlQuery query;
    query.prepare("SELECT id FROM `complex` WHERE name=? LIMIT 1;");
    query.bindValue(0, name);
    qDebug() << "executing query to database: " << query.lastQuery();
    if(!query.exec()){
        qWarning() << "error while getting comlplex data";
        return Q_NULLPTR;
    }
    if(query.first()){
        QSqlRecord rec = query.record();
        ComplexInterface *res = new ComplexInterface(query.value(rec.indexOf("id")).toUInt(), name);
        query.finish();
        return res;
    } else{
        qInfo() << QString("there is no complex with name %1").arg(name);
        return Q_NULLPTR;
    }
}

QVector<Record> ComplexInterface::getSchedule(quint8){
    return {};
}

