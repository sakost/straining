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
#include "ui_mainwindow.h"

#include <algorithm>

#include <QtDebug>
#include <QStandardPaths>
#include <QDir>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>
#include <QScreen>
#include <QVariant>

#include "complexinterface.h"
#include "configurecomplexesdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    if(!initDatabase()){
        QString msg = "database weren't initialized correctly";
        qCritical() << msg;
        QMessageBox errMsg;
        errMsg.setText(msg);
        errMsg.setIcon(QMessageBox::Critical);
        errMsg.exec();
        initialized = false;
        return;
    }
    centrizeWindow();
    connect(this->ui->actionAbout_Qt, SIGNAL(triggered()), QCoreApplication::instance(), SLOT(aboutQt()));
    connect(this->ui->action_Quit, SIGNAL(triggered()), this, SLOT(close()));
    connect(this->ui->actionConfigure_complexes, SIGNAL(triggered()), this, SLOT(configureComplexes()));
}

void MainWindow::centrizeWindow(){
    QScreen *screen = this->screen();
    QRect screenGeometry = screen->geometry();
    int heightWindow, widthWindow;
    heightWindow = screenGeometry.height();
    widthWindow = screenGeometry.width();
    this->move((widthWindow - this->width())/2, (heightWindow - this->height())/2);
}

bool MainWindow::initDatabase(){
    db = QSqlDatabase::addDatabase("QSQLITE");
    QDir path = QDir(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));
    if(!path.exists()){
        path.mkpath(".");
    }
    qInfo() << "database path: " << path.filePath("db.sqlite");
    db.setDatabaseName(path.filePath("db.sqlite"));
    if(!db.open()){
        qWarning() << db.lastError().text() << " path: " << db.databaseName();
        return false;
    }
    return createDatabase();
}

bool MainWindow::createDatabase(){
    QSqlQuery query;
    if(!query.exec("CREATE TABLE IF NOT EXISTS `complex`("
                    "`id` INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
                    "`name` TEXT UNIQUE NOT NULL"
                ");")){
        qWarning() << "couldn't create `complex` table";
        query.finish();
        return false;
    }
    qDebug() << "executed query to database: " << query.lastQuery();
    if(!query.exec("CREATE TABLE IF NOT EXISTS `record`("
                   "`id` INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
                   "`count` INTEGER DEFAULT 0 NOT NULL,"
                   "`relax_seconds` INTEGER DEFAULT 0 NOT NULL,"
                   "`type` TEXT DEFAULT '', /*i.o. meters or empty for reiterations*/"
                   "`date` TEXT DEFAULT (date('now')),"
                   "`time` TEXT DEFAULT (time('now')),"
                   "`complex_id` INTEGER DEFAULT 1,"
                   "FOREIGN KEY(complex_id) REFERENCES complex(id)"
                 ");")){
        qWarning() << "couldn't create `record` table";
        query.finish();
        return false;
    }
    qDebug() << "executed query to database: " << query.lastQuery();
    query.finish();
    return true;

}

void MainWindow::loadComplexes(){
    QSet<ComplexInterface*> complexes = ComplexInterface::getComplexes();
    for (auto el: complexes) {
        if(el != Q_NULLPTR){
            complexesChecked.push_back({el, (settings.value("complexes/" + el->uName, QVariant(false)).toBool())});
            settings.setValue("complexes/" + el->uName, complexesChecked.back().second);
        } else{
            qCritical() << "something went wrong...";
        }
    }
    std::sort(complexesChecked.begin(), complexesChecked.end());
}

MainWindow::~MainWindow()
{
    delete ui;
    if(db.isOpen())
        db.close();
}


void MainWindow::configureComplexes(){
    ConfigureComplexesDialog dialog(complexesChecked, this);
    dialog.exec();
}
