#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQml>

#include "boxesmodel.h"
#include "tile.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterType<Tile>("Tile", 1, 0, "Tile");
    qRegisterMetaType<QObjectList>("QObjectList");
    qmlRegisterType<BoxesModel>("BoxesModel", 1, 0, "BoxesModel");

    engine.load(QUrl(QStringLiteral("qrc:///qml/qml/main.qml")));

    return app.exec();
}
