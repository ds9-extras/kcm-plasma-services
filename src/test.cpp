#include <QApplication>
#include <QDebug>

#include "krunnerservice.h"
#include "balooservice.h"
#include "akonadiservice.h"

int main()
{
    AkonadiService r;
    qDebug() << r.isEnabled();
    r.setEnabled(false);
}
