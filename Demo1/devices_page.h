#ifndef DEVICES_PAGE_H
#define DEVICES_PAGE_H

#include <QObject>

#include "httprequest.h"
#include "httpresponse.h"
#include "httprequesthandler.h"
#include "../../../Documents/FileReadWrite/filejson.h"

using namespace stefanfrings;


class devices_page: public HttpRequestHandler
{
public:
    devices_page();

    void service(HttpRequest& request, HttpResponse& response);

    ToJson *m_json = new ToJson;

    QStringList keys = QStringList();

    QStringList values = QStringList();

    QStringList readkeys(QJsonDocument m_doc);

    QStringList readvalues(QJsonDocument m_doc);
};

#endif // DEVICES_PAGE_H
