#pragma once

#include <QMainWindow>
#include <QSettings>
#include <QSqlDatabase>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QSettings *settings;
    QSqlDatabase db;
    bool initDatabase();
    bool createDatabase();
    bool initComplexes();
    void centrizeWindow();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool initialized = true;

private:
    Ui::MainWindow *ui;
};
