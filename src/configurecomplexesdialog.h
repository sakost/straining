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

#include <QDialog>
#include <QGroupBox>
#include <QBoxLayout>
#include <QCheckBox>

#include "complexinterface.h"

namespace Ui {
class ConfigureComplexesDialog;
}

class ConfigureComplexesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigureComplexesDialog(const QVector< QPair<ComplexInterface*, bool> >& complexes, QWidget *parent = nullptr);
    ~ConfigureComplexesDialog();
    QVector< QCheckBox* > complexes;

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ConfigureComplexesDialog *ui;
};

