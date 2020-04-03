#pragma once
#include <QObject>
#include <QSet>
#include <QString>

#include <record.h>
class ComplexInterface : public QObject
{
    Q_OBJECT

private:
    ComplexInterface(quint64 id, const QString& uName, QObject *parent=Q_NULLPTR);
    static quint64 hasAlreadyComplex(const QString& name);

    static QSet<quint64> *complexIds;

public:
    static QSet<quint64>& getComplexIds();
    static ComplexInterface* getComplex(quint64 id);
    static ComplexInterface* getComplex(const QString& name);
    static bool registerComplex(ComplexInterface *ci);

    ComplexInterface(quint64 id, QObject *parent = nullptr);
    ~ComplexInterface(){};

    QString uName;
    quint64 id;

    virtual QVector<Record> getSchedule(quint8 nDays);
    ComplexInterface(){};
signals:

};

