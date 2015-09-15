#include "src/mainwindow.h"
#include <QApplication>
#include <qsplashscreen.h>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QPixmap pixmap(":/icons/logo.png");
    QSplashScreen splash(pixmap);
    splash.show();

    // Process events :)
    app.processEvents();

    QCoreApplication::setOrganizationName("paalgyula");
    QCoreApplication::setOrganizationDomain("paalgyula.com");
    QCoreApplication::setApplicationName("NodeIDE");

    MainWindow w;
    splash.finish(&w);

    w.setGeometry(QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            w.size(),
            app.desktop()->availableGeometry()));

    w.showMaximized();
    return app.exec();
}
