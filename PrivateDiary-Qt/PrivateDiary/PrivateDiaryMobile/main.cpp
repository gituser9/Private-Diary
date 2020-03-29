#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "statusbar.h"
#include <Model/DataStructure/appdata.h>
#include "Presenter/userpresenter.h"
#include "Presenter/postpresenter.h"
#include "models/postlistmodel.h"
#include "models/postmodel.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);


    qmlRegisterType<StatusBar>("StatusBar", 0, 1, "StatusBar");
    qmlRegisterType<UserPresenter>("UserPresenter", 0, 1, "UserPresenter");
    qmlRegisterType<PostPresenter>("PostPresenter", 0, 1, "PostPresenter");
    qmlRegisterType<PostListModel>("PostListModel", 0, 1, "PostListModel");
    qmlRegisterType<PostModel>("PostModel", 0, 1, "PostModel");


    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated, &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl) {
            QCoreApplication::exit(-1);
        }
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
