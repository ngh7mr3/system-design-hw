#include "NotFound.h"

void NotFoundHandler::handleRequest(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &resp)
{
    send(resp, Poco::Net::HTTPResponse::HTTP_NOT_FOUND, "Not found");
}