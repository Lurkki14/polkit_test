#include <QDebug>
#include <QCoreApplication>
#include <QtDBus/QDBusContext>
#include <QtDBus/QDBusMessage>
#include <QtDBus/QDBusConnection>

#include <polkitqt1-authority.h>

#include "helper.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    helper *hper = new helper;

    QDBusMessage message = QDBusMessage::createMethodCall("org.polkit_test", "/", "org.polkit_test", QLatin1String("action2"));

    if (QDBusConnection::systemBus().call(message, QDBus::NoBlock).type() == QDBusMessage::ReplyMessage) {
        qDebug("successfully called method");
    }
    return a.exec();
}
