#include "complexinterface.h"

#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QDebug>


QSet<quint64> *ComplexInterface::complexIds = Q_NULLPTR;
const QString invalidName = "<NULL>";

QSet<quint64>& ComplexInterface::getComplexIds(){
    if(ComplexInterface::complexIds == Q_NULLPTR){
        ComplexInterface::complexIds = new QSet<quint64>;
    }
    return *ComplexInterface::complexIds;
}

ComplexInterface::ComplexInterface(quint64 id, const QString& uName, QObject *parent):QObject(parent){
    this->id=id;
    this->uName = uName;
}

ComplexInterface::ComplexInterface(quint64 id, QObject *parent) : QObject(parent){
    this->id = id;

    QSqlQuery query;
    query.prepare("SELECT name FROM `complex` WHERE id=? LIMIT 1;");
    query.bindValue(0, QVariant(id));
    qDebug() << "executing query to database: " << query.lastQuery();
    if(!query.exec()){
        qWarning() << QString("error while selecting complex with id %1").arg(id);
        query.finish();
        this->uName = invalidName;
        return;
    }

//    if(query.size() < 1){
//        qWarning() << QString("complex with id %1 was not found").arg(id);
//        query.finish();
//        this->uName = invalidName;
//        return;
//    }
    if(query.first()){
        QSqlRecord rec = query.record();
        this->uName = query.value(rec.indexOf("name")).toString();
    }else{
        this->uName = invalidName;
        qWarning() << QString("there is no complex with id %1").arg(id);
    }
    query.finish();
}


bool ComplexInterface::registerComplex(ComplexInterface *ci){
    if(!dynamic_cast<ComplexInterface*>(ci)){
        return false;
    }
    ci = dynamic_cast<ComplexInterface*>(ci);
    quint64 id;
    if((id = ComplexInterface::hasAlreadyComplex(ci->uName)) > 0){
        ci->id = id;
        return ci;
    }
    QSqlQuery query;
    query.prepare("INSERT INTO complex (name) VALUES (:uName);");
    query.bindValue(":uName", ci->uName);
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

        ComplexInterface::getComplexIds().insert(ci->id);

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
        qWarning() << "error while getting comlplex data";
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

