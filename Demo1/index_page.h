#ifndef INDEX_PAGE_H
#define INDEX_PAGE_H

#include <QObject>

#include "httprequest.h"
#include "httpresponse.h"
#include "httprequesthandler.h"

using namespace stefanfrings;

class index_page : public HttpRequestHandler
{
    Q_OBJECT
    Q_DISABLE_COPY(index_page)
public:

    /** Constructor */
    index_page();

    /** Generates the response */
    void service(HttpRequest& request, HttpResponse& response);

signals:

public slots:
};

#endif // INDEX_PAGE_H
