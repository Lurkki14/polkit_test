QT -= gui
QT += dbus

CONFIG += c++11 console link_pkgconfig
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.=e
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        helper.cpp \
        main.cpp

# Flags for polkit-qt5
PKGCONFIG += polkit-qt5-1

# Default rules for deployment.
dbus_target.path=/usr/share/dbus-1
dbus_target.files = dbus/*

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target dbus_target

HEADERS += \
    helper.h
