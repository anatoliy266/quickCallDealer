#include <QCoreApplication>

#include "generalworker.h"
#include "listenworker.h"

#include <QThread>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QVariant>
#include <QDebug>
#include <QSqlDatabase>
#include <QLocale>

#include <stdlib.h>

int main(int argc, char *argv[])
{
    qDebug() << "started";
    QLocale locale;
    locale.setDefault(QLocale::Russian);
    QCoreApplication a(argc, argv);
    qRegisterMetaType<qintptr>("qintptr");
    QThread* thread1 = new QThread();
    ListenWorker* listenWork = new ListenWorker();
    QObject::connect(thread1, SIGNAL(started()), listenWork, SLOT(createListenSocket()));
    listenWork->moveToThread(thread1);
    thread1->start();

    return a.exec();
}
