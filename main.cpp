#include "mainwindow.h"

#include <QApplication>
#include <QSettings>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setOrganizationName("sakost");
    app.setApplicationName("STraining");

    MainWindow w;
    if(!w.initialized)return -1;
    w.setWindowTitle(app.applicationName());
    w.show();
    return app.exec();
}
