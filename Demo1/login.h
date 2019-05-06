#ifndef LOGIN_H
#define LOGIN_H

#include <QObject>

#include "httprequest.h"
#include "httpresponse.h"
#include "httprequesthandler.h"

using namespace stefanfrings;

class login : public HttpRequestHandler
{
    Q_OBJECT
    Q_DISABLE_COPY(login)
public:
    login();

    void service(HttpRequest &request, HttpResponse &response);
};

#endif // LOGIN_H
