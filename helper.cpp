#include "helper.h"

#include <QtDBus/QDBusContext>
#include <QtDBus/QDBusConnection>
#include <QAction>
#include <QDebug>

#include <polkitqt1-authority.h>
#include <polkitqt1-gui-action.h>

helper::helper(QObject *parent) : QObject(parent)
{
    // Get authorization
    PolkitQt1::UnixProcessSubject subject(static_cast<uint>(QCoreApplication::applicationPid()));

    PolkitQt1::Authority::Result result;
    result = PolkitQt1::Authority::instance()->checkAuthorizationSync("org.polkit_test.action2", subject, PolkitQt1::Authority::AllowUserInteraction);

    if (result == PolkitQt1::Authority::Yes) {
        qDebug("allowed for action2");
    }

    if (!QDBusConnection::systemBus().isConnected()) {
        qDebug("not connected to system bus");
        QCoreApplication::instance()->quit();
    }

    if (!QDBusConnection::systemBus().registerService("org.polkit_test")) {
        qDebug() << "couldn't run helper:" << QDBusConnection::systemBus().lastError().name();
        QCoreApplication::instance()->quit();
    }

    if (!QDBusConnection::systemBus().registerObject("/", this)) {
        qDebug("couldn't register service interface");
        QCoreApplication::instance()->quit();
    }
}
