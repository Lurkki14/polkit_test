#include "helper.h"

#include <QtDBus/QDBusContext>
#include <QtDBus/QDBusConnection>

#include <polkitqt1-authority.h>
helper::helper(QObject *parent) : QObject(parent)
{
    if (!QDBusConnection::systemBus().isConnected()) {
        qDebug("not connected to system bus");
        QCoreApplication::instance()->quit();
    }

    if (!QDBusConnection::systemBus().registerService("org.polkit_test")) {
        qDebug("couldn't run helper");
        QCoreApplication::instance()->quit();
    }

    if (!QDBusConnection::systemBus().registerObject("/", this)) {
        qDebug("couldn't register service interface");
        QCoreApplication::instance()->quit();
    }
}
