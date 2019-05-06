/**
  @file
  @author Stefan Frings
*/

#include "formcontroller.h"
#include <QDebug>

FormController::FormController()
{}

void FormController::service(HttpRequest& request, HttpResponse& response)
{

    response.setHeader("Content-Type", "text/html; charset=ISO-8859-1");

    if (request.getParameter("action")=="show")
    {
        response.write("<html><body>");
        response.write("Name = ");
        response.write(request.getParameter("name"));
        response.write("<br>City = ");
        response.write(request.getParameter("city"));
        response.write("</body></html>",true);
    }
    else if(request.getParameter("foo")=="upvote")
    {
        QString m_tmp = m_json->reloadfile();
        response.write("<html><body>");
        response.write("<form method=\"post\">");
        response.write("  <input type=\"hidden\" name=\"action\" value=\"show\">");
        response.write("  Name: <input type=\"text\" name=\"name\"><br>");
        response.write("  City: <input type=\"text\" name=\"city\"><br>");
        response.write("  <input  type=\"submit\">");
        response.write("</form>");
        response.write("<form id= \"test\" method=\"post\">");
        response.write("  <button name=\"foo\" value=\"upvote\">reloaded</button>");
        response.write("</form>");
        if(m_tmp != nullptr)
        {
            response.write("<div>");
            response.write(m_tmp.toUtf8());
            response.write("</div>");
        }
        response.write("</body></html>",true);
    }
    else
    {
        response.write("<html><body>");
        response.write("<form method=\"post\">");
        response.write("  <input type=\"hidden\" name=\"action\" value=\"show\">");
        response.write("  Name: <input type=\"text\" name=\"name\"><br>");
        response.write("  City: <input type=\"text\" name=\"city\"><br>");
        response.write("  <input  type=\"submit\">");
        response.write("</form>");
        response.write("<form id= \"test\" method=\"post\">");
        response.write("  <button name=\"foo\" value=\"upvote\">reload</button>");
        response.write("</form>");
        response.write("</body></html>",true);
    }
}

