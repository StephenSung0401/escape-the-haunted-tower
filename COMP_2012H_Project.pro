#-------------------------------------------------
#
# Project created by QtCreator 2018-11-26T21:03:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = COMP_2012H_Project
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    gameinstance.cpp \
    Block/door.cpp \
    Block/monster_a.cpp \
    Block/monster_b.cpp \
    Block/monster_c.cpp \
    Block/monster.cpp \
    Block/wall.cpp \
    Block/block.cpp \
    monstericon.cpp \
    items/Diamond.cpp \
    items/Item.cpp \
    items/Key.cpp \
    items/Potion.cpp \
    gamewindow.cpp \
    player/Player.cpp \
    Block/stair.cpp \
    levelmanager.cpp \
    player/playerinfo.cpp \
    Block/exit.cpp \
    items/Desmond.cpp

HEADERS += \
        mainwindow.h \
    gameinstance.h \
    gamewindow.h \
    Block/door_color.h \
    Block/door.h \
    Block/monster_a.h \
    Block/monster_b.h \
    Block/monster_c.h \
    Block/monster.h \
    Block/wall.h \
    Block/block.h \
    monstericon.h \
    items/Diamond.h \
    items/Item.h \
    items/Key.h \
    items/Potion.h \
    player/Player.h \
    Block/stair.h \
    Block/stair_direction.h \
    levelmanager.h \
    player/playerinfo.h \
    Block/exit.h \
    items/Desmond.h

FORMS += \
        mainwindow.ui \
    gamewindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

DISTFILES +=
