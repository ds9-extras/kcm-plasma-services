#include "balooservice.h"

#include <QStandardPaths>
#include <QFileInfo>
#include <QDebug>
#include <QDBusConnection>
#include <QDBusMessage>
#include <QDBusPendingCall>
#include <QProcess>

#include <KConfig>
#include <KConfigGroup>

#include <Baloo/IndexerConfig>


BalooService::BalooService()
{
}

QString BalooService::name() const
{
    return "Baloo";
}

bool BalooService::isEnabled() const
{
    Baloo::IndexerConfig config;
    return config.fileIndexingEnabled();
}

bool BalooService::setEnabled(bool enabled)
{
    Baloo::IndexerConfig config;
    config.setFileIndexingEnabled(enabled);

    // Start Baloo
    if (enabled) {
        const QString exe = QStandardPaths::findExecutable(QStringLiteral("baloo_file"));
        QProcess::startDetached(exe);
    }
    else {
        QDBusMessage message = QDBusMessage::createMethodCall(QStringLiteral("org.kde.baloo"),
                                                              QStringLiteral("/"),
                                                              QStringLiteral("org.kde.baloo.main"),
                                                              QStringLiteral("quit"));

        QDBusConnection::sessionBus().asyncCall(message);
    }

    // Start cleaner
    const QString exe = QStandardPaths::findExecutable(QStringLiteral("baloo_file_cleaner"));
    QProcess::startDetached(exe);

    return true;
}

