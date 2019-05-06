#ifndef USERS_PAGE_H
#define USERS_PAGE_H

#include "httprequest.h"
#include "httpresponse.h"
#include "httprequesthandler.h"
#include <QJsonDocument>
#include <QJsonObject>

using namespace stefanfrings;

class users_page: public HttpRequestHandler
{
public:
    users_page();

    void service(HttpRequest& request, HttpResponse &response);
};

#endif // USERS_PAGE_H
