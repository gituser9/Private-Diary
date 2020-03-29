QT += quick svg

CONFIG += c++17

#INCLUDEPATH += ../PrivateDiaryCore
#LIBS += -L$$PWD/../PrivateDiaryCore -lPrivateDiaryCore

include(../PrivateDiaryCore/PrivateDiaryCore.pri)
include(./statusbar/src/statusbar.pri)

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        models/postlistmodel.cpp \
        models/postmodel.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


#win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../PrivateDiaryCore/release/ -lPrivateDiaryCore
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../PrivateDiaryCore/debug/ -lPrivateDiaryCore
#else:unix: LIBS += -L$$OUT_PWD/../PrivateDiaryCore/ -lPrivateDiaryCore

#INCLUDEPATH += $$PWD/../PrivateDiaryCore
#DEPENDPATH += $$PWD/../PrivateDiaryCore

#win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../PrivateDiaryCore/release/libPrivateDiaryCore.a
#else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../PrivateDiaryCore/debug/libPrivateDiaryCore.a
#else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../PrivateDiaryCore/release/PrivateDiaryCore.lib
#else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../PrivateDiaryCore/debug/PrivateDiaryCore.lib
#else:unix: PRE_TARGETDEPS += $$OUT_PWD/../PrivateDiaryCore/libPrivateDiaryCore.a

DISTFILES += \
    login/Login.qml

HEADERS += \
    models/postlistmodel.h \
    models/postmodel.h
