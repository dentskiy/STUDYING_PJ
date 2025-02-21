QT       += core gui widgets openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

DESTDIR = ../../../build

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../../back/CommandPocket/CommandPocket.cpp \
    ../../back/Controller/Controller.cpp \
    ../../back/MoveStrategy/objMove.cpp \
    ../../back/ObjModel/GetObj.cpp \
    ../../back/ObjModel/ObjectReader.cpp \
    gifmove.cpp \
    main.cpp \
    mainwindow.cpp \
    mementopatrn.cpp \
    myopenglwidget.cpp
    
HEADERS += \
    ../../back/Controller/Controller.h \
    gifmove.h \
    mainwindow.h \
    mementopatrn.h \
    myopenglwidget.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
