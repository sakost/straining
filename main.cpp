#include "mainwindow.h"

#include <QApplication>
#include <QSettings>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
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

    w.show();
    return app.exec();
}
