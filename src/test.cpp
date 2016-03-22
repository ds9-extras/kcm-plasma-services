#include <QApplication>
#include <QDebug>

#include "krunnerservice.h"

int main()
{
    KRunnerService r;
    qDebug() << r.isEnabled();
    r.setEnabled(false);
    qDebug() << r.isEnabled();
    r.setEnabled(true);
    qDebug() << r.isEnabled();
}
