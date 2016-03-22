#include <QApplication>
#include <QDebug>

#include "krunnerservice.h"
#include "balooservice.h"

int main()
{
    BalooService r;
    qDebug() << r.isEnabled();
    r.setEnabled(true);
}
