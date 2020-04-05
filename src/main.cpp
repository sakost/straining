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

#include "mainwindow.h"

#include <QApplication>
#include <QSettings>
#include <QDebug>
#include <QLoggingCategory>

#include "testcomplex.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
#ifndef QT_DEBUG
    QLoggingCategory::setFilterRules("*.debug=false");
    qSetMessagePattern("[%{type}] - %{message}");
#else
    qSetMessagePattern("[%{type}] (%{file}:%{line}) - %{message}");
#endif
    app.setOrganizationName("sakost");
    app.setApplicationName("STraining");
    QIcon icon = QIcon(":/images/logo.ico");
    qDebug() << "app icon: " << icon;
    app.setWindowIcon(icon);

    MainWindow w;


    if(!w.initialized){
        qWarning() << "main window was not initialized";
        return -1;
    }
    w.setWindowTitle(app.applicationName());

    testComplex t; // todo initializing of complexes more easy...
    w.syncComplexesChecked();

    w.show();
    return app.exec();
}
