/**
  @file
  @author Stefan Frings
*/

#include <QCoreApplication>
#include "requestmapper.h"
#include "filelogger.h"
#include "staticfilecontroller.h"
#include "controller/dumpcontroller.h"
#include "controller/templatecontroller.h"
#include "controller/formcontroller.h"
#include "controller/fileuploadcontroller.h"
#include "controller/sessioncontroller.h"
#include "index_page.h"
#include "login.h"
#include "users_page.h"
#include "devices_page.h"
#include "setting_page.h"

/** Redirects log messages to a file */
extern FileLogger* logger;

/** Controller for static files */
extern StaticFileController* staticFileController;

RequestMapper::RequestMapper(QObject* parent)
    :HttpRequestHandler(parent)
{
    qDebug("RequestMapper: created");
}


RequestMapper::~RequestMapper()
{
    qDebug("RequestMapper: deleted");
}


void RequestMapper::service(HttpRequest& request, HttpResponse& response)
{
    QByteArray path=request.getPath();
    qDebug("RequestMapper: path=%s",path.data());

    // For the following pathes, each request gets its own new instance of the related controller.

    if (path.startsWith("/dump"))
    {
        DumpController().service(request, response);
    }

    else if (path.startsWith("/template"))
    {
        TemplateController().service(request, response);
    }

    else if (path.startsWith("/form"))
    {
        FormController().service(request, response);
    }

    else if (path.startsWith("/file"))
    {
        FileUploadController().service(request, response);
    }

    else if (path.startsWith("/session"))
    {
        SessionController().service(request, response);
    }
    else if(path.startsWith("/users"))
    {
        users_page().service(request, response);
    }
    else if(path.startsWith("/devices"))
    {
        devices_page().service(request,response);
    }
    else if(request.getParameter("login") == "confirm")
    {
        bool login_r = m_json->login(request.getParameter("account"), request.getParameter("password"));
        if(request.getParameter("account") == nullptr)
        {
            login_r = false;
        }
        if(login_r)
        {
            index_page().service(request, response);
        }
        else
        {
            login().service(request, response);
        }
    }
    else if(path.startsWith("/settings"))
    {
        setting_page().service(request, response);
    }

    // All other pathes are mapped to the static file controller.
    // In this case, a single instance is used for multiple requests.
    else
    {
        staticFileController->service(request, response);
    }

    qDebug("RequestMapper: finished request");

    // Clear the log buffer
    if (logger)
    {
       logger->clear();
    }
}
