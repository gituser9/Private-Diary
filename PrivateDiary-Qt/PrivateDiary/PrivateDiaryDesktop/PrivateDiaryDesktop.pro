#-------------------------------------------------
#
# Project created by QtCreator 2017-11-12T19:04:55
#
#-------------------------------------------------

QT       += core gui widgets sql network


TARGET = PrivateDiary
TEMPLATE = app

CONFIG += c++17
CONFIG += app_bundle

INCLUDEPATH += ../PrivateDiaryCore
LIBS += -L$$PWD/../PrivateDiaryCore -lPrivateDiaryCore


DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    View/ViewModel/postmodel.cpp \
    View/loginpage.cpp \
    View/mainpage.cpp \
    View/Modal/credentialdialog.cpp

HEADERS += \
    mainwindow.h \
    View/ViewModel//postmodel.h \
    View/loginpage.h \
    View/mainpage.h \
    View/Modal/credentialdialog.h


FORMS += \
    mainwindow.ui \
    View/Modal/credentialdialog.ui

RESOURCES += \
    qrc.qrc

ICON = logo-mac.icns
