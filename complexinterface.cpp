#include "complexinterface.h"

#include <QSqlQuery>
#include <QVariant>
#include <QDebug>

const QString invalidName = "<NULL>";

ComplexInterface::ComplexInterface(quint64 id, QObject *parent) : QObject(parent){
    this->id = id;

    QSqlQuery query;
    query.prepare("SELECT name FROM `complex` WHERE id=? LIMIT 1;");
    query.bindValue(0, QVariant(id));
    query.exec();

    if(query.size() < 1){
        qWarning() << QString("complex with id %1 was not found").arg(id);
        this->uName = invalidName;
        query.finish();
        return;
    }
    this->uName = query.value(0).toString();
    query.finish();
}


bool ComplexInterface::registerComplex(ComplexInterface *ci){
    if(!dynamic_cast<ComplexInterface*>(ci)){
        return false;
    }
    ci = dynamic_cast<ComplexInterface*>(ci);
    QSqlQuery query;
    query.prepare("INSERT INTO complex (name) VALUES (?);");
    query.bindValue(0, ci->uName);
    if(!query.exec() || !query.exec("SELECT id FROM complex ORDER BY id DESC LIMIT 1;")){
        qWarning() << "error while registering complex";
        return false;
    }
    ci->id = query.value(0).toUInt();
    query.finish();

    return true;
}

ComplexInterface* ComplexInterface::getComplex(quint64 id){
    QSqlQuery query;
    query.prepare("SELECT name FROM `complex` WHERE id=? LIMIT 1;");
    query.bindValue(0, id);
    if(!query.exec()){
        qWarning() << "error while getting comlplex data";
        return Q_NULLPTR;
    }
    ComplexInterface *res = new ComplexInterface;
    res->id = id;
    res->uName = query.value(0).toString();
    query.finish();
    return res;
}

ComplexInterface* ComplexInterface::getComplex(const QString &name){
    QSqlQuery query;
    query.prepare("SELECT id FROM `complex` WHERE name=? LIMIT 1;");
    query.bindValue(0, name);
    if(!query.exec()){
        qWarning() << "error while getting comlplex data";
        return Q_NULLPTR;
    }
    ComplexInterface *res = new ComplexInterface;
    res->uName = name;
    res->id = query.value(0).toUInt();
    query.finish();
    return res;
}

QVector<Day> ComplexInterface::getSchedule(quint8){
    return {};
}

