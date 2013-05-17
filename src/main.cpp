#include <QApplication>
#include <QtDeclarative>

#include "downloadercomponent.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

//    Downloader d;
//    gd.downloadSubreddit("aww",1);
//    d.downloadSubreddit("otters",1);
//    gd.downloadSubreddit("otters",2);
//    gd.downloadSubreddit("otters");

    qmlRegisterType<DownloaderComponent>("DownloaderComponent", 1, 0, "Downloader");

    QDeclarativeView view;
    view.setSource(QUrl("qrc:/qml/qml/main.qml"));
    view.show();

    return app.exec();
}
