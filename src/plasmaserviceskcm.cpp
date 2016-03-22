/*
    Copyright 2016 by David Edmundson <davidedmundson@kde.org>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "plasmaserviceskcm.h"

#include <QVBoxLayout>
#include <QCheckBox>
#include <QDebug>



#include <KAboutData>
#include <KTitleWidget>
#include <KPluginFactory>
#include <KLocalizedString>

#include "krunnerservice.h"

#include <kpluginfactory.h>
#include <kpluginloader.h>
K_PLUGIN_FACTORY(PlasmaServicesKcmFactory, registerPlugin<PlasmaServicesKcm>();)
K_EXPORT_PLUGIN(PlasmaServicesKcmFactory("kcm_plasmaservices"))


PlasmaServicesKcm::PlasmaServicesKcm(QWidget *parent, const QVariantList &args) :
    KCModule(parent, args)
{
    KAboutData* aboutData = new KAboutData("kcm_plasmaservices", i18n("Plasma Services Config"), PROJECT_VERSION);

    aboutData->setShortDescription(i18n("Simple Plasma Services Configuration"));
    aboutData->setLicense(KAboutLicense::GPL_V2);
    aboutData->setHomepage("https://github.com");

    aboutData->addAuthor("David Edmundson", i18n("Author"), "davidedmundson@kde.org");

    setAboutData(aboutData);
    
    m_services["krunner"] = new KRunnerService;

    prepareUi();
}

PlasmaServicesKcm::~PlasmaServicesKcm()
{
    qDeleteAll(m_services);
}

/*
 *     bool enabled = m_enableCheckbox->isChecked();
    if (mountPointsEx)
        enabled = false;

    Baloo::IndexerConfig config;
    config.setFileIndexingEnabled(enabled);
    config.setIncludeFolders(includeFolders);
    config.setExcludeFolders(excludeFolders);

    if (m_previouslyEnabled != enabled) {
        config.setFirstRun(true);
    }

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
    **/

// #2 Then add these lines (if they don't exist, else make necessary changes in them) to ~/.config/akonadi/akonadiserverrc
//
// [QMYSQL]
// Name=akonadi
// Host=
// User=
// Password=
// Options="UNIX_SOCKET=/home/manmath/.local/share/akonadi/db_misc/mysql.socket"
// ServerPath=/usr/sbin/mysqld-akonadi
// StartServer=false



void PlasmaServicesKcm::save()
{
}

void PlasmaServicesKcm::prepareUi()
{
    auto layout = new QVBoxLayout;

    auto title = new KTitleWidget(this);
    title->setText(i18n("Plasma Services"));
    layout->addWidget(title);

    foreach(AbstractService *service, m_services.values()) {
        auto checkbox = new QCheckBox(service->name());
        connect(checkbox, &QCheckBox::toggled, this, [this](){changed();});
        checkbox->setChecked(service->isEnabled());
        layout->addWidget(checkbox);
    }
    layout->addStretch();

    setLayout(layout);
}

#include "plasmaserviceskcm.moc"
