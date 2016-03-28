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
#include "akonadiservice.h"
#include "balooservice.h"
#include "kwalletservice.h"

#include <kpluginfactory.h>
#include <kpluginloader.h>
K_PLUGIN_FACTORY(PlasmaServicesKcmFactory, registerPlugin<PlasmaServicesKcm>();)
K_EXPORT_PLUGIN(PlasmaServicesKcmFactory("kcm_plasmaservices"))

#include <QPushButton>
#include <QStylePainter>
#include <QStyleOptionButton>
#include <QPainter>
#include <QPaintEvent>
#include <QEvent>

class ToggleButton : public QAbstractButton
{
public:
    ToggleButton(const QString &text, QWidget *parent = 0);
    virtual ~ToggleButton();
    void paintEvent(QPaintEvent *e) override;
    QSize sizeHint() const override;
protected:
    bool event(QEvent *event) override;
private:
    void initStyle();
    int m_toggleButtonWidth;
};

ToggleButton::ToggleButton(const QString &text, QWidget *parent):
    QAbstractButton(parent)
{
    setText(text);
    setCheckable(true);
    initStyle();
}

ToggleButton::~ToggleButton()
{
}

void ToggleButton::paintEvent(QPaintEvent* e)
{
    QStylePainter p(this);

    const int switchWidth = m_toggleButtonWidth * 2;
    const int switchOffset = width() - switchWidth;

    QRect offArea = QRect(switchOffset, 0, m_toggleButtonWidth, height());
    QRect onArea = QRect(switchOffset + m_toggleButtonWidth, 0, m_toggleButtonWidth, height());

    QStyleOptionProgressBar o;
    QStyleOptionButton o2;
    o2.rect = rect().adjusted(0,0,-switchWidth, 0);
    o2.initFrom(this);
    o2.features = QStyleOptionButton::None;
    o2.text = text();

    o.initFrom(this);
    o.minimum = 0;
    o.maximum = 1;
    o.progress = 1;
    o.textVisible = false;
    p.drawControl(QStyle::CE_CheckBoxLabel, o2);

    o.rect = QRect(switchOffset, 0, switchWidth, height());
    p.drawControl(QStyle::CE_ProgressBarGroove, o);

    if (isChecked()) {
        p.drawControl(QStyle::CE_ProgressBarContents, o);
    }

    o2.rect = isChecked() ? onArea : offArea;
    p.drawControl(QStyle::CE_PushButtonBevel, o2);


    if (isChecked()) {
        o.rect = offArea;
        o.text=i18n("On");
        p.drawControl(QStyle::CE_ProgressBarLabel, o);
//         p.drawItemText(offArea, Qt::AlignCenter, palette(), true, i18n("On"));
    } else {
        p.drawItemText(onArea, Qt::AlignCenter, palette(), false, i18n("Off"));
    }
}

QSize ToggleButton::sizeHint() const
{
    QFontMetrics fm = fontMetrics();

    QStyleOptionButton opt;
    opt.initFrom(this);
    const QSize buttonSize(style()->sizeFromContents(QStyle::CT_PushButton, &opt, QSize(m_toggleButtonWidth * 2, fm.height()), this));
    return QSize(buttonSize.width() + fm.width(text()), buttonSize.height());
}

bool ToggleButton::event(QEvent* event)
{
    if (event->type() == QEvent::FontChange ||
        event->type() == QEvent::StyleChange)
    {
        initStyle();
    }
    return QAbstractButton::event(event);
}

void ToggleButton::initStyle()
{
    QFontMetrics fm = fontMetrics();
    m_toggleButtonWidth = qMax(fm.width(i18n("On")), fm.width(i18n("Off"))) + style()->pixelMetric(QStyle::PM_ButtonMargin) * 4;
}

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
    m_services["akonadi"] = new AkonadiService;
    m_services["baloo"] = new BalooService;
    m_services["kwallet"] = new KWalletService;

    prepareUi();
}

PlasmaServicesKcm::~PlasmaServicesKcm()
{
    qDeleteAll(m_services);
}

void PlasmaServicesKcm::save()
{
    QMap<QString, AbstractService*>::const_iterator i = m_services.constBegin();
    while (i != m_services.constEnd()) {
        bool checked = m_checkboxes[i.key()]->isChecked();
        if (i.value()->isEnabled() != checked) {
            i.value()->setEnabled(checked);
        }
        i++;
    }
}

void PlasmaServicesKcm::prepareUi()
{
    auto layout = new QVBoxLayout;

    QMap<QString, AbstractService*>::const_iterator i = m_services.constBegin();
    while (i != m_services.constEnd()) {
        AbstractService *service = i.value();
        auto checkbox = new ToggleButton(service->name());
        m_checkboxes[i.key()] = checkbox;

        connect(checkbox, &QAbstractButton::toggled, this, [this](){changed();});
        checkbox->setChecked(service->isEnabled());
        layout->addWidget(checkbox);
        i++;
    }
    layout->addStretch();

    setLayout(layout);
}

#include "plasmaserviceskcm.moc"
