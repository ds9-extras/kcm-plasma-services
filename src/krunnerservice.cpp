#include "krunnerservice.h"

#include <QStandardPaths>
#include <QFileInfo>
#include <QDebug>

#include <KConfig>
#include <KConfigGroup>

KRunnerService::KRunnerService()
{
}

QString KRunnerService::name() const
{
    return "KRunner";
}

bool KRunnerService::isEnabled() const
{
    //create a list of autostart directories that klauncher will use
    QStringList dirs = QStandardPaths::locateAll(QStandardPaths::GenericConfigLocation, QStringLiteral("autostart"), QStandardPaths::LocateDirectory);

    bool hasEntry = false;
    foreach(const QString &dir, dirs) {
        const QString filePath = dir + "/krunner.desktop";
        if (QFileInfo::exists(filePath)) {
            KConfig autoStartConfig(filePath, KConfig::NoGlobals);
            bool hidden = autoStartConfig.group("Desktop Entry").readEntry("Hidden", false);

            if (hidden) {
                return false;
            }
            hasEntry = true;
        }
    }

    if (hasEntry) {
        //exists and isn't disabled
        return true;
    } else {
        //.desktop file doesn't exist at all, app probably doesn't exist at all therefore disabled
        return false;
    }
}

bool KRunnerService::setEnabled(bool enabled)
{
    const QString userAutostartDir = QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation) + QStringLiteral("/autostart");
    const QString userKRunnerDesktop =  userAutostartDir + "/krunner.desktop";
    if (enabled) {
        QFile file(userKRunnerDesktop);
        file.remove();
    } else {
        KConfig config(userKRunnerDesktop);
        config.group("Desktop Entry").writeEntry("Hidden", true);
    }

    //a system dir could be disabling krunner further up the chain
    //so us adding/removing the file won't do a lot
    return isEnabled() == enabled;
}

