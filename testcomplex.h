#pragma once

#include <QObject>
#include <complexinterface.h>


class testComplex : public ComplexInterface
{
public:
    testComplex();
    QVector<Record> getSchedule(quint8 nDays);
};

