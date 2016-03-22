#include "akonadiservice.h"

#include <QStandardPaths>
#include <QFileInfo>
#include <QDebug>
#include <QProcess>

#include <KConfig>
#include <KConfigGroup>

AkonadiService::AkonadiService()
{
}

QString AkonadiService::name() const
{
    return "Akonadi";
}

bool AkonadiService::isEnabled() const
{
    KConfig config(QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation) + QStringLiteral("/akonadi/akonadiserverrc"));
    return config.group("QMYSQL").readEntry("StartServer", true);
    return true;
}

bool AkonadiService::setEnabled(bool enabled)
{
    KConfig config(QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation) + QStringLiteral("/akonadi/akonadiserverrc"));
    config.group("QMYSQL").writeEntry("StartServer", enabled);

    const QString exe = QStandardPaths::findExecutable(QStringLiteral("akonadictl"));
    QProcess::startDetached(exe, QStringList() << (enabled ? QStringLiteral("start") : QStringLiteral("stop")));

    return true;
}

