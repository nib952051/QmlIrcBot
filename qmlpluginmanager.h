/*
 * Copyright (C) 2008-2015 The Communi Project
 * and nib952051@gmail.com
 *
 * This example is free, and not covered by the BSD license. There is no
 * restriction applied to their modification, redistribution, using and so on.
 * You can study them, modify them, use them in your own program - either
 * completely or partially.
 */

#ifndef QMLPLUGINMANAGER_H
#define QMLPLUGINMANAGER_H

#include <QtCore/QObject>
#include <QtQml/QQmlParserStatus>

class QmlPluginManager : public QObject, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)
    Q_PROPERTY(QString pluginPath MEMBER m_pluginPath NOTIFY pluginPathChanged)

public:
    QmlPluginManager(QObject *parent = 0);
    ~QmlPluginManager();

    void classBegin();
    void componentComplete();

private:
    void loadPlugins();

signals:
    void pluginPathChanged();

private:
    QString m_pluginPath;

};

#endif // QMLPLUGINMANAGER_H
