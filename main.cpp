#include <QDebug>
#include <QCoreApplication>
#include <QtDBus/QDBusContext>
#include <QtDBus/QDBusConnection>

#include <polkitqt1-authority.h>

#include "helper.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    helper *hper = new helper;


    return a.exec();
}
