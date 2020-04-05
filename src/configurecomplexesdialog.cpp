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

#include "configurecomplexesdialog.h"
#include "ui_configurecomplexesdialog.h"

#include <QSizePolicy>

ConfigureComplexesDialog::ConfigureComplexesDialog(const QVector< QPair<ComplexInterface*, bool> >& complexes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigureComplexesDialog)
{
    ui->setupUi(this);

    this->complexes = QVector<QCheckBox*>();
    QVBoxLayout *vLayout = this->ui->verticalLayout_2;
    vLayout->setAlignment(Qt::AlignTop);
    for(auto &el: complexes){
        QHBoxLayout *hLayout = new QHBoxLayout;
        QCheckBox* checkBox = new QCheckBox(el.first->uName);
        checkBox->setChecked(el.second);
        this->complexes.push_back(checkBox);
        hLayout->addWidget(checkBox);
        hLayout->setSizeConstraint(QLayout::SetMinimumSize);
        vLayout->addLayout(hLayout);
    }
}

ConfigureComplexesDialog::~ConfigureComplexesDialog()
{
    delete ui;
}

void ConfigureComplexesDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
