#include "jsonrpcengine.h"

JsonRpcEngine::JsonRpcEngine(QObject *parent) : QObject(parent)
{

}

QString JsonRpcEngine::_method(KerioMethod method)
{
    QString _p_str = "\"%1\":\"%2\"";
    QString _pa_str = "\"%1\":[%2]";
    QString _po_str = "\"%1\":%2";
    QString _ptry_str = "\"%1\":%2";
    QString _string = "";
    QString jBody = "";
    bool proceed = false;
    switch(method)
    {
    case LogIn:
    {
        QString _app = "{" + _p_str.arg("name").arg("%3") +","+_p_str.arg("vendor").arg("%4") +","+_p_str.arg("version").arg("%5") + "}";
        QString _param = "{" + _p_str.arg("userName").arg("%1") +","+_p_str.arg("password").arg("%2") +","+_ptry_str.arg("application").arg(_app) + "}";
        jBody = "{" + _p_str.arg("jsonrpc").arg("2.0") +","+_ptry_str.arg("id").arg(1) +","+_p_str.arg("method").arg("Session.login") +","+_ptry_str.arg("params").arg("%1")+ "}";
        _string = jBody.arg(_param);
        proceed = true;
        break;
    };
    case LogOff:
    {
        jBody = "{" + _p_str.arg("jsonrpc").arg("2.0") +","+_p_str.arg("id").arg(1) +","+_p_str.arg("token").arg("%1")+","+_p_str.arg("method").arg("Session.logout")+"}";
        _string = jBody;
        proceed = true;
        break;
    };
    case CallHistory:
    {
        QString _order = "{"+_p_str.arg("columnName").arg("%4") + "," + _p_str.arg("direction").arg("%5") +"}";
        QString _query = "{" + _p_str.arg("limit").arg("%2") + "," + _p_str.arg("start").arg("%3") + "," + _pa_str.arg("orderBy").arg(_order) +"}";
        QString _property = "{" + _po_str.arg("query").arg(_query) + "}";
        jBody = "{" + _p_str.arg("jsonrpc").arg("2.0") +","+_po_str.arg("id").arg("1") +","+_p_str.arg("token").arg("%1") +","+_p_str.arg("method").arg("Status.getCalls")+","+_po_str.arg("params").arg(_property)+"}";
        _string = jBody;
        proceed = true;
        break;
    };
    case Queue:
    {
        QString _query = "{}";
        QString _property = "{" + _po_str.arg("query").arg(_query) + "," + _po_str.arg("extension").arg("%2") + "}";

        jBody = "{" + _p_str.arg("jsonrpc").arg("2.0") +","+_po_str.arg("id").arg("1") +","+_p_str.arg("token").arg("%1") +","+_p_str.arg("method").arg("Status.getQueueAgents")+","+_po_str.arg("params").arg(_property)+"}";
        _string = jBody;
        proceed = true;
        break;
    };
    case NoMethod:
    {
        proceed = false;
        break;
    };
    case DownloadRec:
    {
        QString _property = "{" + _p_str.arg("id").arg("%2") + "," + _p_str.arg("transcode").arg("false") + "}";

        jBody = "{" + _po_str.arg("jsonrpc").arg("2.0") +","+_p_str.arg("id").arg(1) +","+_p_str.arg("token").arg("%1") +","+_p_str.arg("method").arg("Recordings.downloadAudioContent")+","+_po_str.arg("params").arg(_property)+"}";

        _string = jBody;

        proceed = true;
        break;
    };
    }
    QString result = "";
    if (proceed)
    {
        //_string = "{jsonrpc:2.0,\"id\":1,\"method\":\"Session.login\",\"params\":{\"userName\":\"a.stanevich\",\"password\":\"256532fdnjvfn73501505\",\"application\":{\"name\":\"KerioOperatorServ\",\"vendor\":\"King Anthony\",\"version\":\"0.1\"}}}";
        result = _string;
    }
    return result;
}

QHash<KerioParams, QVariant> JsonRpcEngine::checkRequiredParams(KerioMethod method, QHash<KerioParams, QVariant> params)
{
    bool check = false;
    switch (method) {
    case LogIn:
    {
        if (params[Login] != NULL)
        {
            check = true;
        } else {
            check = false;
            break;
        }
        if (params[Pwd] != NULL)
        {
            check = true;
        } else {
            check = false;
            break;
        }
        if (params[AppName] == NULL)
            params[AppName] = "/Default App/";
        if (params[AppVendor] == NULL)
            params[AppVendor] = "/Default Vendor/";
        if (params[AppRev] == NULL)
            params[AppRev] = "/1.0/";
        break;
    };
    case LogOff:
    {
        if (params[Token] == NULL)
        {
            check = false;
        } else {
            check = true;
        }
        break;
    };
    case CallHistory:
    {
        if (params[Token] == NULL)
        {
            check = false;
        } else {
            if (params[Limit] == "")
            {
                params[Limit] = 200;
            }
            if (params[Start] == "")
            {
                params[Start] = 0;
            }
            if (params[OrderField] == "")
            {
                params[OrderField] = "ANSWERED_DURATION";
            }
            if (params[Direction] == NULL)
            {
                params[Direction] = "Desc";
            }
            if (params[Fields] == "")
            {
                QStringList list;
                list.append("TIMESTAMP,");
                list.append(" FROM_NUM,");
                list.append(" TO_NUM,");
                list.append(" STATUS,");
                list.append(" ANSWERED_DURATION");
                params[Fields] = list;
            }
            if (params[ConditionField] == "")
            {
                params[ConditionField] = "TIMESTAMP";
            }
            if (params[TimeFrom] == NULL)
            {
                params[TimeFrom] = 0;
            }
            if (params[TimeTo] == NULL)
            {
                QDateTime dt = QDateTime::currentDateTime();
                params[TimeTo] = dt.toTime_t();
            }
            check = true;
        }
        break;
    };
    case Queue:
    {
        if (params[Token] == NULL)
        {
            check = false;
        } else {
            if (params[Extension] == NULL)
            {
                check = false;
                break;
            } else {
                check = true;
            }
        }
        break;
    };
    case NoMethod:
    {
        check = false;
        break;
    };
    case DownloadRec:
    {
        if (params[Token] == NULL)
        {
            check = false;
        } else {
            if (params[RecordId] == NULL)
            {
                check = false;
                break;
            } else {
                if (params[Transcode] == NULL)
                {
                    params[Transcode] = false;
                }
                check = true;
            }
        }
        break;
    };
    }
    if (check)
    {
        return params;
    } else {
        params.clear();
        params[Failed] = 1;
        return params;
    }
}

QHash<QString, QVariant> JsonRpcEngine::parse(QString jString)
{
    QHash<QString, QVariant> result;
    QHash<QString, QVariant> token_hash;
    QHash<QString, QVariant> fields_values;
    QHash<QString, QVariant> agents_values;
    QHash<QString, QVariant> calls_values;
    QHash<QString, QVariant> error_hash;
    QJsonDocument jDoc = QJsonDocument::fromJson(jString.toUtf8());
    auto resultJObj = jDoc.object()["result"].toObject();
    auto jKeys = jDoc.object()["result"].toObject().toVariantHash().keys();
    for (int i = 0; i < jKeys.count(); i++)
    {
        if (jKeys.value(i) == "token")
        {
            token_hash[jKeys.value(i)] = resultJObj[jKeys.value(i)].toString();
            result = token_hash;
            break;
        } else {
            if (jKeys.value(i) == "callHistory")
            {
                int totalItems = 0;
                if (!resultJObj["totalItems"].isNull())
                    totalItems = resultJObj["totalItems"].toInt();
                auto callHistoryStruct = resultJObj["callHistory"];

                if (totalItems == 0)
                {
                    fields_values["totalItems"] = 0;
                } else {
                    fields_values["totalItems"] = totalItems;
                    auto callHistoryArray = callHistoryStruct.toArray();
                    for (int j = 0; j < totalItems; j++)
                    {
                        auto members = callHistoryArray.at(j).toObject().toVariantHash().keys();
                        auto values = callHistoryArray.at(j).toObject().toVariantHash().values();
                        QStringList row;
                        for (int q = 0; q < members.count(); q++)
                        {
                            row.append(members.value(q) + "@" + values.value(q).toString());
                        }
                        fields_values[QString::number(j)] = row;
                        row.clear();
                    }
                    result = fields_values;
                    break;
                }
            }
            if (jKeys.value(i) == "agents")
            {
                int totalItems = 0;
                if (!resultJObj["totalItems"].isNull())
                {
                    totalItems = resultJObj["totalItems"].toInt();
                }
                auto agentsStruct = resultJObj["agents"];
                if (totalItems == 0)
                {
                    agents_values["totalItems"] = 0;
                } else {
                    agents_values["totalItems"] = totalItems;
                }
                auto agentsArray = agentsStruct.toArray();
                for (int j = 0; j < totalItems; j++)
                {
                    auto members = agentsArray.at(j).toObject().toVariantHash().keys();
                    auto values = agentsArray.at(j).toObject().toVariantHash().values();
                    QStringList row;
                    for (int q = 0; q < members.count(); q++)
                    {
                        row.append(members.value(q) + "@" + values.value(q).toString());
                    }
                    agents_values[QString::number(j)] = row;
                    row.clear();
                }
                result = agents_values;
                break;
            }
            if (jKeys.value(i) == "recordingList")
            {
                break;
            }
            if (jKeys.value(i) == "fileDownload")
            {
                break;
            }
            if (jKeys.value(i) == "calls")
            {
                int totalItems = 0;
                if (!resultJObj["totalItems"].isNull())
                {
                    totalItems = resultJObj["totalItems"].toInt();
                }
                auto callsStruct = resultJObj["calls"];
                if (totalItems == 0)
                {
                    calls_values["totalItems"] = 0;
                } else {
                    calls_values["totalItems"] = totalItems;
                }
                auto callsArray = callsStruct.toArray();
                for (int j = 0; j < totalItems; j++)
                {
                    auto members = callsArray.at(j).toObject().toVariantHash().keys();
                    auto values = callsArray.at(j).toObject().toVariantHash().values();
                    QStringList row;
                    for (int q = 0; q < members.count(); q++)
                    {
                        if (members.value(q) == "FROM")
                        {
                            auto fromStruct = callsArray.at(j).toObject()["FROM"].toObject();
                            row.append(members.value(q) + "@" + fromStruct["NUMBER"].toString());
                        } else {
                            if (members.value(q) == "TO")
                            {
                                auto toStruct = callsArray.at(j).toObject()["TO"].toObject();
                                row.append(members.value(q) + "@" + toStruct["NUMBER"].toString());
                            } else {
                                row.append(members.value(q) + "@" + values.value(q).toString());
                            }
                        }
                    }
                    calls_values[QString::number(j)] = row;
                    row.clear();
                }
                result = calls_values;
                break;
            }
            if (jKeys.count() == 0)
            {
                result["redirectUrl"]  = "https://ats.550550.ru:4021/admin/login";
                break;
            }
        }
    }
    return result;
}

std::string JsonRpcEngine::generate(KerioMethod method, QHash<KerioParams, QVariant> params)
{
    QString arg1 = "";
    QString arg2 = "";
    QString arg3 = "";
    QString arg4 = "";
    QString arg5 = "";
    QString arg6 = "";
    QString arg7 = "";
    QString arg8 = "";
    QString arg9 = "";
    QString arg10 = "";

    auto _json = _method(method);

    auto _parameters = checkRequiredParams(method, params);

    if (_parameters[Failed] != 1)
    {
        QString result_json = "";
        if (method != NoMethod)
        {
            switch (method) {
            case LogIn:
            {
                arg1 = _parameters[Login].toString();
                arg2 = _parameters[Pwd].toString();
                arg3 = _parameters[AppName].toString();
                arg4 = _parameters[AppVendor].toString();
                arg5 = _parameters[AppRev].toString();
                result_json = _json.arg(arg1).arg(arg2).arg(arg3).arg(arg4).arg(arg5);
                break;
            };
            case LogOff:
            {
                arg1 = _parameters[Token].toString();
                result_json = _json.arg(arg1);
                break;
            };
            case CallHistory:
            {
                arg1 = _parameters[Token].toString();
                arg2 = QString::number(-1);
                arg3 = QString::number(0);
                arg4 = _parameters[OrderField].toString();

                if(_parameters[Direction].toInt() == 1)
                    arg5 = "Desc";
                else
                    arg5 = "Asc";
                result_json = _json.arg(arg1).arg(arg2).arg(arg3).arg(arg4).arg(arg5);
                break;
            };
            case Queue:
            {
                arg1 = _parameters[Token].toString();
                arg2 = _parameters[Extension].toString();
                result_json = _json.arg(arg1).arg(arg2);
                break;
            };
            case DownloadRec:
            {
                arg1 = _parameters[Token].toString();
                arg2 = _parameters[RecordId].toString();
                arg3 = _parameters[Transcode].toString();
                result_json = _json.arg(arg1).arg(arg2);
                break;
            };
            default: {
                generate(KerioMethod::NoMethod, params);
                break;
            }
            }
            return result_json.toStdString();
        } else {
            qDebug() << "Method are not specified!";
            return "";
        }
    } else {
        qDebug() << "Not enought parameters";
        return "";
    }
}
