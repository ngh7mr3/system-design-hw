#pragma once
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>

#include <map>

#include "RequestHandler.h"

class RequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory
{
    typedef Poco::Net::HTTPRequestHandler *(*HandlerCreator)();

    static std::map<std::string, HandlerCreator> _handlers;
    static Poco::Net::HTTPRequestHandler *getHandler(const std::string &func);

  public:
    virtual Poco::Net::HTTPRequestHandler *createRequestHandler(const Poco::Net::HTTPServerRequest &);
    static void Register(const std::string &func, const HandlerCreator &creator);
};