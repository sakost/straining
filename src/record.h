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

#define ALL_COMPLEXES 0

#include <QObject>
#include <QDateTime>
#include <QSqlDatabase>

class ComplexInterface;

class Record : public QObject
{
    Q_OBJECT
private:
    quint64 id;
    quint64 count;
    quint64 relax_seconds;
    QString type;
    QDate date;
    QTime time;
    quint64 complex_id;
    ComplexInterface *complex;
    Record(quint64 id, quint64 count, quint64 relax_seconds, QString type, QDate date, QTime time, quint64 complex_id, QObject *parent = nullptr);
public:
    static Record *createRecord(quint64 complex_id, quint64 count=0, quint64 relax_seconds=0, QString type="", QDate *date=Q_NULLPTR, QTime *time=Q_NULLPTR);
    static QVector<Record> *getRecords(quint64 complex_id=ALL_COMPLEXES, QDate *date=Q_NULLPTR);

    Record(quint64 id, QObject *parent = nullptr);

};

