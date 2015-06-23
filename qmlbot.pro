
TEMPLATE = app
TARGET = qmlbot
DEPENDPATH += .
INCLUDEPATH += .
CONFIG += console c++11
QT = core network qml
DEFINES += QT_NO_CAST_FROM_ASCII QT_NO_CAST_TO_ASCII

lessThan(QT_MAJOR_VERSION, 5)|lessThan(QT_MINOR_VERSION, 1) {
    error(Qt 5.1 or newer required but Qt $$[QT_VERSION] was detected.)
}


## CHECK_INCLUDE_FILES(`Communi/IrcCore/IrcCore' HAVE_COMMUNI_DEV_H)    ## Probably is ok
## CHECK_QML_IMPORT(Communi HAVE_COMMUNI_QML_IMPORT)                    ## Perfect!:)
    
    
# Input
HEADERS += qmlpluginmanager.h
SOURCES += qmlpluginmanager.cpp main.cpp

OTHER_FILES += qml/* qml/plugins/* README.md
