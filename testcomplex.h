#pragma once

#include <complexinterface.h>


class testComplex : public ComplexInterface
{
public:
    QVector<Day> getSchedule(quint8 nDays);
};

