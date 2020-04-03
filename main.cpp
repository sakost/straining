#include "mainwindow.h"

#include <QApplication>
#include <QSettings>
#include <QDebug>
#include <QLoggingCategory>

#include "testcomplex.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    qSetMessagePattern("[%{type}] %{if-debug}(%{file}:%{line}) %{endif}- %{message}");
#ifndef QT_DEBUG
    QLoggingCategory::setFilterRules("*.debug=false");
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

    testComplex();

    w.show();
    return app.exec();
}
