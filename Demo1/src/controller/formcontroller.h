/**
  @file
  @author Stefan Frings
*/

#ifndef FORMCONTROLLER_H
#define FORMCONTROLLER_H

#include "httprequest.h"
#include "httpresponse.h"
#include "httprequesthandler.h"
#include "../../../Documents/FileReadWrite/filejson.h"

using namespace stefanfrings;

/**
  This controller displays a HTML form and dumps the submitted input.
*/


class FormController : public HttpRequestHandler {
    Q_OBJECT
    Q_DISABLE_COPY(FormController)
public:

    /** Constructor */
    FormController();

    /** Generates the response */
    void service(HttpRequest& request, HttpResponse& response);

    ToJson *m_json = new ToJson;
};

#endif // FORMCONTROLLER_H
