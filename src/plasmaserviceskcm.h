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
#ifndef PLASMASERVICESKCM_H
#define PLASMASERVICESKCM_H

#include <KCModule>

class AbstractService;
class QAbstractButton;

class PlasmaServicesKcm : public KCModule
{
    Q_OBJECT
public:
    explicit PlasmaServicesKcm(QWidget *parent, const QVariantList &args);
    ~PlasmaServicesKcm();

public slots:
    void save();

private:
    void prepareUi();

    QHash<QString, AbstractService *> m_services;
    QHash<QString, QAbstractButton *> m_checkboxes;

};

#endif // SDDMKCM_H
