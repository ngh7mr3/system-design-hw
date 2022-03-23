#include "RequestHandler.h"

#include <iostream>

using namespace Poco;
using namespace Poco::Net;

void RequestHandler::send(HTTPServerResponse &resp, HTTPResponse::HTTPStatus status, Poco::JSON::Object::Ptr data)
{
    resp.setStatus(status);
    resp.setContentType("application/json");
    std::ostream &out = resp.send();
    Poco::JSON::Stringifier::stringify(data, out);
    out.flush();
}

void RequestHandler::send(HTTPServerResponse &resp, HTTPResponse::HTTPStatus status, Poco::JSON::Array::Ptr array)
{
    resp.setStatus(status);
    resp.setContentType("application/json");
    std::ostream &out = resp.send();
    Poco::JSON::Stringifier::stringify(array, out);
    out.flush();
}

void RequestHandler::send(HTTPServerResponse &resp, HTTPResponse::HTTPStatus status, const std::string &data)
{
    resp.setStatus(status);
    resp.setContentType("text/html");
    resp.send() << data;
}

std::string RequestHandler::getParam(const URI::QueryParameters &params, const std::string &name)
{
    for (auto &i : params)
        if (i.first == name)
            return i.second;

    return std::string("");
}

HTTPMethodCode RequestHandler::methodCode(const std::string &val)
{
    if (val == "GET")
        return HTTPMethodCode::GET;
    if (val == "POST")
        return HTTPMethodCode::POST;

    return HTTPMethodCode::UNKNOWN;
}