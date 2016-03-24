#include "kwalletservice.h"

#include <QStandardPaths>
#include <QFileInfo>
#include <QDebug>
#include <QProcess>

#include <KConfig>
#include <KConfigGroup>

KWalletService::KWalletService()
{
}

QString KWalletService::name() const
{
    return "KWallet";
}

bool KWalletService::isEnabled() const
{
    KConfig config("kwalletrc");
    KConfigGroup group = config.group("Wallet");
    group.readEntry("Enabled", true);
}

bool KWalletService::setEnabled(bool enabled)
{
    KConfig config("kwalletrc");
    KConfigGroup group = config.group("Wallet");
    group.writeEntry("Enabled", enabled);
    return true;
}

