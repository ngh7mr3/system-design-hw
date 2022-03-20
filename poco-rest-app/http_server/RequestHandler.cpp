#include "RequestHandler.h"

#include <iostream>

using namespace Poco::Net;
using http_server::RequestHandler;

void RequestHandler::handleRequest(HTTPServerRequest &req, HTTPServerResponse &resp)
{
    std::cout << '[' << req.getMethod() << ']' << ' ' << req.getURI() << std::endl;

    Poco::JSON::Object::Ptr root = new Poco::JSON::Object();
    root->set("request_uri", req.getURI());
    root->set("request_method", req.getMethod());

    send(resp, HTTPResponse::HTTP_OK, root);
}

void RequestHandler::send(HTTPServerResponse& resp, HTTPResponse::HTTPStatus status, Poco::JSON::Object::Ptr data)
{
    resp.setStatus(status);
    resp.setContentType("application/json");
    std::ostream& out = resp.send();
    Poco::JSON::Stringifier::stringify(data, out);
    out.flush();
}