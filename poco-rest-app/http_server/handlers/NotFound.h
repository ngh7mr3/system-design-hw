#include "../RequestHandler.h"

class NotFoundHandler : public RequestHandler
{
public:
    NotFoundHandler(){};
    void handleRequest(Poco::Net::HTTPServerRequest& req, Poco::Net::HTTPServerResponse& resp);
};