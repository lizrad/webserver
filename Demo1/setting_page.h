#ifndef SETTING_PAGE_H
#define SETTING_PAGE_H

#include <QObject>

#include "httprequest.h"
#include "httpresponse.h"
#include "httprequesthandler.h"
#include <QJsonDocument>
#include <QJsonObject>

using namespace stefanfrings;


class setting_page: public HttpRequestHandler
{
public:
    setting_page();

    void service(HttpRequest& request, HttpResponse& response);

    QJsonDocument updatekeys(HttpRequest &request, QJsonDocument m_doc);

    QString findkeywords(QJsonDocument m_doc, QString key);

    QStringList findChildren(QJsonDocument m_doc);

    QStringList m_keys = QStringList();
};

#endif // SETTING_PAGE_H
