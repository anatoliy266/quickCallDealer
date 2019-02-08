#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QLocale>

#include "datacontroller.h"
#include "datasocket.h"
#include "diffmodel.h"
#include "databuffer.h"

int main(int argc, char *argv[])
{

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qRegisterMetaType<QList<QVariantList>>("QList<QVariantList>");

    /*QSystemTrayIcon* icon = new QSystemTrayIcon();
    QIcon _icon;
    _icon.addFile("phoneLogo.png");
    qDebug() << _icon;
    icon->setIcon(_icon);
    icon->setVisible(true);
    icon->show();*/

    QThread* thread = new QThread();
    DataSocket* socket = new DataSocket();

    QThread* thread1 = new QThread();
    DataBuffer* buffer = new DataBuffer();

    DataController dtControl;
    DiffModel cMod;
    DiffModel oMod;
    DiffModel qMod;
    DiffModel uMod;

    cMod.setTableName("callsDealer");
    oMod.setTableName("orgsPhones");
    qMod.setTableName("query_type");
    uMod.setTableName("users");

//---------------------------------------
//  send to server connections
    QObject::connect(&dtControl, SIGNAL(sendToServer(QByteArray)), socket, SLOT(writeRequest(QByteArray)), Qt::QueuedConnection);
    QObject::connect(&dtControl, SIGNAL(sendOToServer(QByteArray)), socket, SLOT(writeRequest(QByteArray)), Qt::QueuedConnection);
    QObject::connect(&dtControl, SIGNAL(sendQToServer(QByteArray)), socket, SLOT(writeRequest(QByteArray)), Qt::QueuedConnection);
    QObject::connect(&dtControl, SIGNAL(sendUpdToServer(QByteArray)), socket, SLOT(writeRequest(QByteArray)), Qt::QueuedConnection);
//--------------------------

//---------------------------------------
//  models prepare signals connections
    QObject::connect(&cMod, SIGNAL(cSucess()), &dtControl, SLOT(cModSucess()), Qt::QueuedConnection);
    QObject::connect(&cMod, SIGNAL(hSucess()), &dtControl, SLOT(hModSucess()), Qt::QueuedConnection);
    QObject::connect(&oMod, SIGNAL(sucess()), &dtControl, SLOT(oModSucess()), Qt::QueuedConnection);
    QObject::connect(&qMod, SIGNAL(sucess()), &dtControl, SLOT(qModSucess()), Qt::QueuedConnection);
    QObject::connect(&uMod, SIGNAL(sucess()), &dtControl, SLOT(uModSucess()), Qt::QueuedConnection);
    //nothing
    QObject::connect(&cMod, SIGNAL(nothing(QString)), &dtControl, SLOT(nothing(QString)), Qt::QueuedConnection);
    QObject::connect(&oMod, SIGNAL(nothing(QString)), &dtControl, SLOT(nothing(QString)), Qt::QueuedConnection);
    QObject::connect(&qMod, SIGNAL(nothing(QString)), &dtControl, SLOT(nothing(QString)), Qt::QueuedConnection);
    QObject::connect(&uMod, SIGNAL(nothing(QString)), &dtControl, SLOT(nothing(QString)), Qt::QueuedConnection);
    //authorization
    QObject::connect(&uMod, SIGNAL(authSucess()), &dtControl, SLOT(authSucess()), Qt::QueuedConnection);

//--------------------------

//--------------------------
//  current user data to dtControll connection
    QObject::connect(&uMod, SIGNAL(userProperties(QString, qlonglong)), &dtControl, SLOT(userProperties(QString, qlonglong)));
//--------------------------


//--------------------------
//  data from socket to buffer connections
    QObject::connect(socket, SIGNAL(responseData(QByteArray)), buffer, SLOT(recieveFromServer(QByteArray)), Qt::QueuedConnection);
//--------------------------


//-------------------------
//  queue data from models in buffer
    QObject::connect(&dtControl, SIGNAL(toBuffer(QString, int)), buffer, SLOT(askForTableData(QString, int)), Qt::QueuedConnection);

//-------------------------


//--------------------------
//  sent data from buffer to models connections
    QObject::connect(buffer, SIGNAL(orgsData(QString, QList<QVariantList>)), &oMod, SLOT(model(QString, QList<QVariantList>)), Qt::QueuedConnection);
    QObject::connect(buffer, SIGNAL(usersData(QString, QList<QVariantList>)), &uMod, SLOT(model(QString, QList<QVariantList>)), Qt::QueuedConnection);
    QObject::connect(buffer, SIGNAL(querysData(QString, QList<QVariantList>)), &qMod, SLOT(model(QString, QList<QVariantList>)), Qt::QueuedConnection);
    QObject::connect(buffer, SIGNAL(callsData(QString, QList<QVariantList>)), &cMod, SLOT(model(QString, QList<QVariantList>)), Qt::QueuedConnection);
//-------------------------


//--------------------------
//  from buffer to dtControl prepare signals connections
    QObject::connect(buffer, SIGNAL(orgsPrepared()), &dtControl, SLOT(orgsSucess()), Qt::QueuedConnection);
    QObject::connect(buffer, SIGNAL(usersPrepared()), &dtControl, SLOT(usersSucess()), Qt::QueuedConnection);
    QObject::connect(buffer, SIGNAL(querysPrepared()), &dtControl, SLOT(querysSucess()), Qt::QueuedConnection);
    QObject::connect(buffer, SIGNAL(callsPrepared()), &dtControl, SLOT(callsSucess()), Qt::QueuedConnection);

//--------------------------
//  on app form closed connections
    QObject::connect(&app, SIGNAL(lastWindowClosed()), socket, SLOT(lastWindowClosed()), Qt::QueuedConnection);
//-------------------------


//-------------------------
//  preLoad info connections
    QObject::connect(socket, SIGNAL(failedConnection()), &dtControl, SLOT(failedConnection()), Qt::QueuedConnection);
    QObject::connect(socket, SIGNAL(establishedConnection()), &dtControl, SLOT(establishedConnection()), Qt::QueuedConnection);
//-------------------------


//-------------------------
//  init connections
    QObject::connect(thread, SIGNAL(started()), socket, SLOT(prepareConnection()), Qt::QueuedConnection);
    QObject::connect(&dtControl, SIGNAL(prepareConnection()), thread, SLOT(start()));
//-------------------------


//-------------------------
//  app terminate connections
    QObject::connect(socket, SIGNAL(disconnected()), thread, SLOT(quit()), Qt::QueuedConnection);
    QObject::connect(thread, SIGNAL(finished()), socket, SLOT(deleteLater()));
    QObject::connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
//-------------------------

    socket->moveToThread(thread);
    buffer->moveToThread(thread1);

    thread->start();
    thread1->start();

    QQmlApplicationEngine engine;

    QQmlContext* context = engine.rootContext();
    context->setContextProperty("dtControl", &dtControl);
    context->setContextProperty("oMod", &oMod);
    context->setContextProperty("cMod", &cMod);
    context->setContextProperty("uMod", &uMod);
    context->setContextProperty("qMod", &qMod);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
