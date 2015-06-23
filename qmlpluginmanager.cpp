/*
 * Copyright (C) 2008-2015 The Communi Project
 * and nib952051@gmail.com
 *
 * This example is free, and not covered by the BSD license. There is no
 * restriction applied to their modification, redistribution, using and so on.
 * You can study them, modify them, use them in your own program - either
 * completely or partially.
 */

#include <QtCore/QDebug>
#include <QtCore/QDir>
#include <QtCore/QMetaType>
#include <QtCore/QMetaProperty>
#include <QtCore/QVector>
#include <QtQml/QQmlContext>
#include <QtQml/QQmlComponent>
#include <QtQml/QQmlEngine>


#include "qmlpluginmanager.h"

namespace {

struct Cache
{
    QObject *o;
    QQmlComponent *c;
};

QObject *findMetaTypeInCache(int pluginObjectType, const QVector<Cache> &cache)
{
    foreach (const Cache &cacheItem, cache) {
        QByteArray ba(cacheItem.o->metaObject()->className());
        ba.append('*');
        if (pluginObjectType == QMetaType::type(ba))
            return cacheItem.o;
    }
    return 0;
}

} // End of anonymous namespace


QmlPluginManager::QmlPluginManager(QObject *parent) :
    QObject(parent)
{
}

QmlPluginManager::~QmlPluginManager() {}

void QmlPluginManager::classBegin()
{
}

void QmlPluginManager::componentComplete()
{
    loadPlugins();
}

void QmlPluginManager::loadPlugins()
{
    QVector<Cache> pluginLoadingCache;

    const QString pluginBaseDir = QLatin1String("./qml/") + m_pluginPath + QLatin1Char('/');
    QDir d(pluginBaseDir);
    QStringList plugins = d.entryList(QDir::Files);

    //! plugins: resolve, beginCreate
    foreach (const QString &pluginName, plugins) {
        const QString nextPluginUri = pluginBaseDir + pluginName;
        QQmlEngine *engine = QtQml::qmlEngine(this);
        QQmlComponent *component = new QQmlComponent(engine, QUrl::fromLocalFile(nextPluginUri));
        QObject *obj = component->beginCreate(engine->rootContext());

        if (!component->errors().isEmpty()) {
            qDebug() << pluginName << component->errors();
            delete obj; //! @todo test me
            continue;
        }

        pluginLoadingCache.push_back(Cache{obj, component});
    }

    foreach (const Cache &cacheItem, pluginLoadingCache) {
        const QMetaObject *metaObject = cacheItem.o->metaObject();
        for (int i = metaObject->propertyOffset(); i < metaObject->propertyCount(); ++i) {
            QMetaProperty nextProperty = metaObject->property(i);

            const int nextPropertyType = nextProperty.userType();
            QMetaType::TypeFlags nextPropertyFlags = QMetaType::typeFlags(nextPropertyType);
            const QVariant nextPropertyValue = nextProperty.read(cacheItem.o);
            if (nextPropertyFlags.testFlag(QMetaType::PointerToQObject)
                    && nextPropertyValue.value<QObject *>() == 0) {
                if (QObject *found = findMetaTypeInCache(nextPropertyType, pluginLoadingCache)) {
                    nextProperty.write(cacheItem.o, QVariant::fromValue(found));
                }
            }
        }
    }

    foreach (const Cache &cacheItem, pluginLoadingCache)
        cacheItem.c->completeCreate();
}
