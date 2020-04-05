# Copyright © 2020 by sakost
#
# This file is part of STraining, a Qt-based application for simplify trainings.
#
# STraining is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.


QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += src/complexinterface.cpp \
           src/configurecomplexesdialog.cpp \
           src/mainwindow.cpp \
           src/record.cpp \
           src/testcomplex.cpp \
           src/main.cpp

HEADERS += src/complexinterface.h \
           src/configurecomplexesdialog.h \
           src/mainwindow.h \
           src/record.h \
           src/testcomplex.h

FORMS += src/mainwindow.ui \
    src/configurecomplexesdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    main.qrc

DISTFILES += \
    LICENSE
