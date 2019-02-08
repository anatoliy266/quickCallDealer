#include "datacontroller.h"
#include <QDebug>

DataController::DataController(QObject *parent): QObject(parent)
{

}

void DataController::init()
{
    emit prepareConnection();
}

void DataController::orgsRequest()
{
    qDebug() << "orgs";
    QByteArray request;
    QString table = "orgsPhones";
    QString query = "";
    QDataStream in(&request, QIODevice::ReadWrite);
    in << quint8();
    in << table;
    in << query;
    in.device()->seek(0);
    in << quint8(request.size()-sizeof(quint8));
//    qDebug() << Q_FUNC_INFO << request.size();
//    qDebug() << Q_FUNC_INFO << table;
//    qDebug() << Q_FUNC_INFO << query;
    emit sendOToServer(request);
}

void DataController::querysRequest()
{
    qDebug() << Q_FUNC_INFO << "querys";
    QByteArray request;
    QString table = "query_type";
    QString query = "";
    QDataStream in(&request, QIODevice::ReadWrite);
    in << quint8();
    in << table;
    in << query;
    in.device()->seek(0);
    in << quint8(request.size()-sizeof(quint8));
//    qDebug() << Q_FUNC_INFO << request.size();
//    qDebug() << Q_FUNC_INFO << table;
//    qDebug() << Q_FUNC_INFO << query;
    emit sendQToServer(request);
}

void DataController::usersRequest()
{
    qDebug() << Q_FUNC_INFO << "users";
    QByteArray request;
    QString table = "users";
    QString query = "";
    QDataStream in(&request, QIODevice::ReadWrite);
    in << quint8();
    in << table;
    in << query;
    in.device()->seek(0);
    in << quint8(request.size()-sizeof(quint8));
//    qDebug() << Q_FUNC_INFO << request.size();
//    qDebug() << Q_FUNC_INFO << table;
//    qDebug() << Q_FUNC_INFO << query;
    emit sendToServer(request);
}

void DataController::modelRequest(int userphone)
{
    qDebug() << Q_FUNC_INFO << userphone << "calls request";
    QByteArray request;
    QString table = "callsDealer";
    QString query = "agentPhone = '"+QString::number(userphone)+"'";
    QDataStream in(&request, QIODevice::ReadWrite);
    in << quint8();
    in << table;
    in << query;
    in.device()->seek(0);
    in << quint8(request.size()-sizeof(quint8));
    emit sendToServer(request);
}

QString DataController::user()
{
    return _user;
}

void DataController::setUser(QString user)
{
    qDebug() << Q_FUNC_INFO << user;
    _user = user;
    emit userChanged(_user);
}

qlonglong DataController::num()
{
    return _number;
}

void DataController::setNum(qlonglong num)
{
    qDebug() << Q_FUNC_INFO << num;
    _number = num;
    emit numChanged(_number);
}

void DataController::setRecRequest(QString _idx, QString userName, QString orgName, QString orgPhone, QString query, QString comment, QString image)
{
    qDebug() << Q_FUNC_INFO << "completing call" << _idx << userName << orgName << orgPhone << query << comment << image;
    int idx = _idx.toInt();
    QImage _image_;
    _image_.load(image.split("qrc:/content/").value(1));
    qlonglong _orgPhone = orgPhone.toLongLong();
    QByteArray _image;
    QDataStream _in(&_image, QIODevice::WriteOnly);
    _in << _image_;
    QByteArray request;
    QString _table = "update";
    QString _query1 = "UPDATE callsDealer SET query = '"+query+"', comment = '"+comment+"', writed = 1 WHERE id_call = "+QString::number(idx);
    QString _query2 = "UPDATE orgsPhones SET orgName = '"+orgName+"', userName = '"+userName+"', image = '"+_image+"' WHERE orgPhone = "+QString::number(_orgPhone);
    QString _query = _query1 + "[delimiter]"+ _query2;
    QDataStream in(&request, QIODevice::ReadWrite);
    in << quint8();
    in << _table;
    in << _query;
    in.device()->seek(0);
    in << quint8(request.size()-sizeof(quint8));
//    qDebug() << Q_FUNC_INFO << request.size();
//    qDebug() << Q_FUNC_INFO << _table;
//    qDebug() << Q_FUNC_INFO << _query;
    emit sendUpdToServer(request);
}

void DataController::establishedConnection()
{
    qDebug() << Q_FUNC_INFO;
    emit establishedConnectionSignal();
}
void DataController::failedConnection()
{
    qDebug() << Q_FUNC_INFO;
    emit failedConnectionSignal();
}

void DataController::preloadSucess()
{
    qDebug() << Q_FUNC_INFO;
    emit preloadSucessSignal();
}

void DataController::userProperties(QString user, qlonglong number)
{
    qDebug() << Q_FUNC_INFO << user << number;
    setUser(user);
    setNum(number);
}

void DataController::callsSucess()
{
    qDebug() << Q_FUNC_INFO;
    emit callsSucessSignal();
}

void DataController::usersSucess()
{
    qDebug() << Q_FUNC_INFO;
    emit usersSucessSignal();
}

void DataController::orgsSucess()
{
    qDebug() << Q_FUNC_INFO;
    emit orgsSucessSignal();
}

void DataController::querysSucess()
{
    qDebug() << Q_FUNC_INFO;
    emit querysSucessSignal();
}

void DataController::authSucess()
{
    emit authSucessSignal();
}

void DataController::nothing(QString table)
{
    QStringList tList({"users", "orgsPhones", "query_type", "callsDealer"});
    switch (tList.indexOf(table)) {
    case 0: {
        qDebug() << "users NY signal";
        emit uModNYSignal();
        break;
    }
    case 1: {
        qDebug() << "orgs NY signal";
        emit oModNYSignal();
        break;
    }
    case 2: {
        qDebug() << "query NY signal";
        emit qModNYSignal();
        break;
    }
    case 3: {
        qDebug() << "calls NY signal";
        emit cModNYSignal();
    }
    }
}

void DataController::uModSucess()
{
    emit uModSucessSignal();
}

void DataController::cModSucess()
{
    emit cModSucessSignal();
}

void DataController::hModSucess()
{
    emit hModSucessSignal();
}

void DataController::qModSucess()
{
    emit qModSucessSignal();
}

void DataController::oModSucess()
{
    oModSucessSignal();
}

void DataController::queueData(QString table, int filter)
{
    qDebug() << Q_FUNC_INFO << table << filter;
    emit toBuffer(table, filter);
}
