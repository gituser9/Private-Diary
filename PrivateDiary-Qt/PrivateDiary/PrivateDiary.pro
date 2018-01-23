#-------------------------------------------------
#
# Project created by QtCreator 2017-11-12T19:04:55
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = PrivateDiary
TEMPLATE = app

CONFIG += c++14


DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    View/ViewModel/postmodel.cpp \
    Model/DataStructure/post.cpp \
    Presenter/postpresenter.cpp \
    Model/Service/userservice.cpp \
    Presenter/userpresenter.cpp \
    View/loginpage.cpp \
    Util/qaesencryption.cpp \
    Util/crypter.cpp \
    Model/DataStructure/appdata.cpp \
    View/mainpage.cpp \
    Model/Service/postservice.cpp \
    Util/aes.c \
    View/Modal/credentialdialog.cpp

HEADERS += \
        mainwindow.h \
    View/ViewModel//postmodel.h \
    Model/DataStructure/post.h \
    Model/DataStructure/pages.h \
    Model/DataStructure/constant.h \
    Model/DataStructure/user.h \
    Presenter/postpresenter.h \
    Model/Service/userservice.h \
    Presenter/userpresenter.h \
    View/loginpage.h \
    Util/qaesencryption.h \
    Util/crypter.h \
    Model/DataStructure/appdata.h \
    View/mainpage.h \
    Model/Service/postservice.h \
    Util/aes.h \
    View/Modal/credentialdialog.h


FORMS += \
        mainwindow.ui \
    View/Modal/credentialdialog.ui

RESOURCES += \
    qrc.qrc
