QT -= gui
QT += sql

INCLUDEPATH += $$PWD

CONFIG += c++17

SOURCES += \
    $$PWD/Syncer/qjsonwebtoken.cpp \
    $$PWD/Syncer/syncer.cpp \
    $$PWD/privatediarycore.cpp \
    $$PWD/Model/DataStructure/post.cpp \
    $$PWD/Presenter/postpresenter.cpp \
    $$PWD/Model/Service/userservice.cpp \
    $$PWD/Presenter/userpresenter.cpp \
    $$PWD/Util/qaesencryption.cpp \
    $$PWD/Util/crypter.cpp \
    $$PWD/Model/DataStructure/appdata.cpp \
    $$PWD/Model/Service/postservice.cpp \
    $$PWD/Util/aes.c

HEADERS += \
    $$PWD/Syncer/qjsonwebtoken.h \
    $$PWD/Syncer/syncer.h \
    $$PWD/PrivateDiaryCore_global.h \
    $$PWD/privatediarycore.h \
    $$PWD/Model/DataStructure/post.h \
    $$PWD/Model/DataStructure/pages.h \
    $$PWD/Model/DataStructure/constant.h \
    $$PWD/Model/DataStructure/user.h \
    $$PWD/Presenter/postpresenter.h \
    $$PWD/Model/Service/userservice.h \
    $$PWD/Presenter/userpresenter.h \
    $$PWD/Util/qaesencryption.h \
    $$PWD/Util/crypter.h \
    $$PWD/Model/DataStructure/appdata.h \
    $$PWD/Model/Service/postservice.h \
    $$PWD/Util/aes.h
