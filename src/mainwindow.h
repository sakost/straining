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

#include <QMainWindow>
#include <QSettings>
#include <QSqlDatabase>

#include "complexinterface.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QSettings settings;
    QSqlDatabase db;
    QVector< QPair< ComplexInterface*, bool > > complexesChecked;

    bool initDatabase();
    bool createDatabase();
    void centrizeWindow();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool initialized = true;
    void syncComplexesChecked();

private:
    Ui::MainWindow *ui;

public slots:
    void configureComplexes();
};
