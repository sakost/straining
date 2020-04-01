#pragma once

#include <QObject>
#include <QVector>

class Data;


class Data : public QObject
{
    Q_OBJECT
public:
    Data(quint64 count, quint64 relaxSeconds, QString type, quint8 number, QObject *parent = nullptr) : QObject(parent), count(count), relaxSeconds(relaxSeconds), type(type), number(number){};
//    Data(const Data&, QObject *parent = nullptr);

    quint64 toDb(quint64 record_id); // returns id
    bool isSynced();

    static Data *fromDb(quint64 id);
private:

    explicit Data(QObject *parent = nullptr);
    quint64 id;
    quint64 count;
    quint64 relaxSeconds;
    QString type;
    quint8 number;

signals:

};

