QT       += core gui sql multimedia
QT += concurrent
QT += gui-private

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = uni_game
TEMPLATE = app

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    number_of_players.cpp \
    result.cpp \
    scene.cpp

HEADERS += \
    login.h \
    mainwindow.h \
    number_of_players.h \
    result.h \
    scene.h

FORMS += \
    login.ui \
    mainwindow.ui \
    number_of_players.ui \
    result.ui \
    scene.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
