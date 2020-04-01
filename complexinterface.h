#pragma once

#include <QObject>
#include <QMap>
#include <QString>

#include <record.h>
class ComplexInterface : public QObject
{
    Q_OBJECT

public:
    static ComplexInterface* getComplex(quint64 id);
    static ComplexInterface* getComplex(const QString& name);
    static bool registerComplex(ComplexInterface *ci);

    ComplexInterface(quint64 id, QObject *parent = nullptr);
    explicit ComplexInterface(QObject *parent = nullptr) : QObject(parent){};
    ~ComplexInterface(){};

    QString uName;
    quint64 id;

    virtual QVector<Day> getSchedule(quint8 nDays);


signals:

};

