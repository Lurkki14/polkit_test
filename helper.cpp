#include "helper.h"

#include <QtDBus/QDBusContext>
#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusConnectionInterface>
#include <QDebug>
#include <QStringLiteral>

#include <polkitqt1-authority.h>

#include "/opt/cuda/include/nvml.h"

helper::helper(QObject *parent) : QObject(parent)
{
    // Check if registration succeeded
    //connect(QDBusConnection::systemBus().interface(), &QDBusConnectionInterface::serviceRegistered, [=](const QString &name){qDebug() << name;});

    /*
    // Get authorization
    PolkitQt1::UnixProcessSubject subject(static_cast<uint>(QCoreApplication::applicationPid()));

    PolkitQt1::Authority::Result result;
    result = PolkitQt1::Authority::instance()->checkAuthorizationSync("org.polkit_test.action2", subject, PolkitQt1::Authority::AllowUserInteraction);

    if (result != PolkitQt1::Authority::Yes) {
        qDebug("not allowed for action2");
        QCoreApplication::instance()->quit();
    }
    */
    // Check if the service is already registered

    //qDebug() << QDBusConnection::systemBus().interface()->serviceOwner("org.polkit_test");

    // Re-register the service
    /*if (QDBusConnection::systemBus().interface()->registerService("org.polkit_test", QDBusConnectionInterface::ServiceQueueOptions::ReplaceExistingService, QDBusConnectionInterface::AllowReplacement) == QDBusConnectionInterface::ServiceRegistered) {
        qDebug("succesfully registered service");
    }*/

    if (!QDBusConnection::systemBus().registerService("org.polkit_test")) {
        qDebug() << "unable to register service:" << QDBusConnection::systemBus().lastError().message();
        QCoreApplication::instance()->quit();
    }

    if (!QDBusConnection::systemBus().registerObject("/", this, QDBusConnection::ExportAllSlots)) {
        qDebug("couldn't register service interface");
        QCoreApplication::instance()->quit();
    }
}

void helper::action2() {
    qDebug("performing action2");

    // Get authorization
    PolkitQt1::UnixProcessSubject subject(static_cast<uint>(QCoreApplication::applicationPid()));

    PolkitQt1::Authority::Result result;
    result = PolkitQt1::Authority::instance()->checkAuthorizationSync("org.polkit_test.action2", subject, PolkitQt1::Authority::AllowUserInteraction);

    if (result != PolkitQt1::Authority::Yes) {
        qDebug("not allowed for action2");
        return;
    }

    nvmlInit_v2();
    nvmlDevice_t dev;
    if (nvmlDeviceGetHandleByIndex_v2(0, &dev) != NVML_SUCCESS) {
        return;
    }
    if (nvmlDeviceSetPowerManagementLimit(dev, 150000) != NVML_SUCCESS) {
        nvmlShutdown();
        return;
    }
    qDebug("successfully assigned power limit");
    nvmlShutdown();
}
