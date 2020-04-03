#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStandardPaths>
#include <QDir>
#include <QtDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>
#include <QScreen>

#include <complexinterface.h>

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
    connect(this->ui->actionAbout_Qt, SIGNAL(triggered()), QCoreApplication::instance(), SLOT(aboutQt()));
    connect(this->ui->action_Quit, SIGNAL(triggered()), this, SLOT(close()));
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

bool MainWindow::initComplexes(){
    return true; // todo initializing of complexes more easy...
}

MainWindow::~MainWindow()
{
    delete ui;
    delete settings;
    if(db.isOpen())
        db.close();
}

