QT -= gui
QT += sql

TARGET = PrivateDiaryCore
TEMPLATE = lib
DEFINES += PRIVATEDIARYCORE_LIBRARY

DESTDIR = $$PWD

CONFIG += c++17


# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    privatediarycore.cpp \
    Model/DataStructure/post.cpp \
    Presenter/postpresenter.cpp \
    Model/Service/userservice.cpp \
    Presenter/userpresenter.cpp \
    Util/qaesencryption.cpp \
    Util/crypter.cpp \
    Model/DataStructure/appdata.cpp \
    Model/Service/postservice.cpp \
    Util/aes.c \

HEADERS += \
    PrivateDiaryCore_global.h \
    privatediarycore.h \
    Model/DataStructure/post.h \
    Model/DataStructure/pages.h \
    Model/DataStructure/constant.h \
    Model/DataStructure/user.h \
    Presenter/postpresenter.h \
    Model/Service/userservice.h \
    Presenter/userpresenter.h \
    Util/qaesencryption.h \
    Util/crypter.h \
    Model/DataStructure/appdata.h \
    Model/Service/postservice.h \
    Util/aes.h \

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
#ios {
#    CONFIG += staticlib # since you're probably building a shared library by default
#    CONFIG += framework
#}
#macx|ios {
#    CONFIG += lib_bundle
#    FRAMEWORK_HEADERS.version = Versions
#    FRAMEWORK_HEADERS.files = $${HEADERS}
#    FRAMEWORK_HEADERS.path = Headers
#    QMAKE_BUNDLE_DATA += FRAMEWORK_HEADERS    # If we're static but a bundle, we want to copy files to a
#    # framework directory.
#    CONFIG(staticlib, shared|staticlib){
#        message("Adding copy for static framework")
#        # (using QMAKE_EXTRA_TARGET will be executed before
#        # linking, which is too early).
#        QMAKE_POST_LINK += mkdir -p $${TARGET}.framework/Headers && \
#            $$QMAKE_COPY $$PWD/*.h $${TARGET}.framework/Headers && \
#            $$QMAKE_COPY $$OUT_PWD/lib$${TARGET}.a $${TARGET}.framework/$${TARGET} && \
#            $$QMAKE_RANLIB -s $${TARGET}.framework/$${TARGET}
#    }
#}
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    PrivateDiaryCore.pri
