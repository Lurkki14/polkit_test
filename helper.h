#pragma once

#include <QtCore/QCoreApplication>
#include <QtDBus/QDBusContext>

class helper : public QObject, protected QDBusContext
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.polkit_test")
public:
    explicit helper(QObject *parent = nullptr);

    void action2();
signals:

public slots:
};

