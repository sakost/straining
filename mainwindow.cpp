#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStandardPaths>
#include <QDir>
#include <QtDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>
#include <QScreen>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    settings = new QSettings(QSettings::UserScope);
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
        return false;
    }
    if(!query.exec("CREATE TABLE IF NOT EXISTS `record`("
                     "`id` INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
                     "`complex_id` INTEGER,"
                     "`date` TEXT,"
                     "FOREIGN KEY(complex_id) REFERENCES complex(id)"
                 ");")){
        qWarning() << "couldn't create `record` table";
        return false;
    }
    if(!query.exec("CREATE TABLE IF NOT EXISTS `set`("
                     "`id` INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
                     "`count` INTEGER DEFAULT 0 NOT NULL,"
                     "`relax_seconds` INTEGER NOT NULL,"
                     "record_id INTEGER,"
                     "`number` INTEGER NOT NULL,"
                     "`type` TEXT, /*i.o. meters or empty for reiteration*/"
                     "FOREIGN KEY (record_id) REFERENCES record(id)"
                   ");")){
        qWarning() << "couldn't create `set` table";
        return false;
    }
    return true;

}

MainWindow::~MainWindow()
{
    delete ui;
    delete settings;
    if(db.isOpen())
        db.close();
}

