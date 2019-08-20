QT -= gui
QT += dbus widgets

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

HEADERS += \
    helper.h

# Flags for polkit-qt5
PKGCONFIG += polkit-qt5-1

LIBS += -lnvidia-ml

# Default rules for deployment.
dbus_interface_target.path=/usr/share/dbus-1/interfaces
dbus_interface_target.files=dbus/org.polkit_test.xml

dbus_service_target.path=/usr/share/dbus-1/services
dbus_service_target.files=dbus/org.polkit_test.service

dbus_policy_target.path=/usr/share/dbus-1/system.d
dbus_policy_target.files=dbus/org.polkit_test.conf

polkit_policy_target.path=/usr/share/polkit-1/actions
polkit_policy_target.files=polkit/org.polkit_test.policy

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target dbus_interface_target dbus_service_target dbus_policy_target polkit_policy_target

