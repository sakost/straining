#include "data.h"

#include <QSqlQuery>
#include <QVariant>
#include <QVariantList>
#include <QDebug>

Data::Data(QObject *parent) : QObject(parent){}


quint64 Data::toDb(quint64 record_id){
    QVariantList params;
    params.append(this->count);
    params.append(this->relaxSeconds);
    params.append(this->number);
    params.append(record_id);

    QSqlQuery query;

    query.prepare(QString("INSERT INTO set (count, relax_seconds, type, number, record_id)"
                          " VALUES (?, ?, ?, ?, ?);"));

    for(int i = 0; i < params.size(); i ++){
       query.bindValue(i, params[i]);
    }

    if(!query.exec()){
        qWarning() << "error while adding data";
        return 0;
    }

    query.finish();

    if(!query.exec("SELECT id FROM set ORDER BY id DESC LIMIT 1;")){
        qWarning() << "can't get last added set";
        return 0;
    }
    return this->id = query.value(0).toUInt();
}

bool Data::isSynced(){
    return id != 0;
}

Data *Data::fromDb(quint64 id){
    Data *res = new Data;
    QSqlQuery query;
    query.prepare("SELECT count, relax_seconds, type, number FROM `set` WHERE id=? LIMIT 1;");
    query.bindValue(0, id);
    if(!query.exec()){
        qWarning() << "error while getting data";
        return res;
    }

    res->count = query.value(0).toUInt();
    res->relaxSeconds = query.value(1).toUInt();
    res->type = query.value(2).toString();
    res->number = query.value(3).toUInt();

    return res;
}


