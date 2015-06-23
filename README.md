#QmlIrcBot

This is simple bot writen in qml, inspired by [qt_gerrit bot](https://github.com/rburchell/gerritbot2).
It extends [libcommuni example](https://github.com/communi/libcommuni/tree/master/examples/qmlbot).
It has plugin loading feature based on [DI](https://en.wikipedia.org/wiki/Dependency_injection).


## Boring part

It has no deployment rules(for shadow builds) and qrc yet. Compiled binary requires "qml/main.qml" in Qt.application.dirPath and qml Communi plugin.
