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

#pragma once
#include <QObject>
#include <QSet>
#include <QString>

#include "record.h"
class ComplexInterface : public QObject
{
    Q_OBJECT

private:
    ComplexInterface(quint64 id, const QString& uName, QObject *parent=Q_NULLPTR);
    static quint64 hasAlreadyComplex(const QString& name);

    static QSet<ComplexInterface*> *complexes;

public:
    static QSet<ComplexInterface*>& getComplexes();
    static ComplexInterface* getComplex(quint64 id);
    static ComplexInterface* getComplex(const QString& name);
    static bool registerComplex(ComplexInterface *ci);

    ~ComplexInterface(){};

    QString uName;
    quint64 id;

    virtual QVector<Record> getSchedule(quint8 nDays);
    ComplexInterface(){};
signals:

};

