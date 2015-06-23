/*
 * Copyright (C) 2008-2015 The Communi Project
 * and nib952051@gmail.com
 *
 * This example is free, and not covered by the BSD license. There is no
 * restriction applied to their modification, redistribution, using and so on.
 * You can study them, modify them, use them in your own program - either
 * completely or partially.
 */

#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/qqml.h>

#include "qmlpluginmanager.h"


int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    app.setOrganizationName(QLatin1String("QmlIrcBot"));
    app.setOrganizationDomain(QLatin1String("qt.io"));
    app.setApplicationName(QLatin1String("QmlIrcBot"));

    // enable debug output
    // qputenv("IRC_DEBUG", "1");

    qmlRegisterType<QmlPluginManager>("QmlIrcBot.Utils", 0, 1, "PluginManager");
    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("./qml/main.qml")));

    return app.exec();
}
