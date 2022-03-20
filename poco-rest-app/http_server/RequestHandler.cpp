#include "RequestHandler.h"

#include <iostream>
#include <Poco/JSON/Object.h>

using namespace Poco::Net;
using http_server::RequestHandler;

void RequestHandler::handleRequest(HTTPServerRequest &req, HTTPServerResponse &resp)
{
    std::cout << '[' << req.getMethod() << ']' << ' ' << req.getURI() << std::endl;

    resp.setStatus(HTTPResponse::HTTP_OK);
    resp.setContentType("application/json");

    Poco::JSON::Object::Ptr root = new Poco::JSON::Object();
    root->set("request_uri", req.getURI());
    root->set("request_method", req.getMethod());

    std::ostream& out = resp.send();
    Poco::JSON::Stringifier::stringify(root, out);
    out.flush();
}