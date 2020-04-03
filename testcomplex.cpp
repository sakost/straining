#include <QDebug>

#include "testcomplex.h"

testComplex::testComplex(){
    this->uName = "test complex";
    ComplexInterface::registerComplex(this);
}

QVector<Record> testComplex::getSchedule(quint8){
    return {};
}
