#include "HttpServer.h"

#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/HTTPServerParams.h>
#include <Poco/Net/ServerSocket.h>
#include <Poco/Net/SocketAddress.h>

#include <iostream>

#include "RequestHandlerFactory.h"
#include "handlers/Person.h"

using Poco::Net::HTTPServer;
using Poco::Net::HTTPServerParams;
using Poco::Net::ServerSocket;
using Poco::Net::SocketAddress;
using Poco::Util::Application;
using Poco::Util::OptionSet;
using Poco::Util::ServerApplication;

using http_server::HttpServer;

HttpServer::HttpServer()
{
}
HttpServer::~HttpServer()
{
}

void HttpServer::initialize(Application &self)
{
    loadConfiguration();
    RequestHandlerFactory::Register("/person", &PersonHandler::create);
    ServerApplication::initialize(self);
}

void HttpServer::uninitialize()
{
    ServerApplication::uninitialize();
}

void HttpServer::defineOptions(OptionSet &options)
{
    ServerApplication::defineOptions(options);
}

int HttpServer::main([[maybe_unused]] const std::vector<std::string> &args)
{
    unsigned short port = (unsigned short)config().getInt("HttpServer.port", 8080);

    ServerSocket svs(SocketAddress("0.0.0.0", port));
    HTTPServer srv(new RequestHandlerFactory, svs, new HTTPServerParams);

    std::cout << "Starting server on port " << port << std::endl;
    srv.start();
    waitForTerminationRequest();
    srv.stop();

    return Application::EXIT_OK;
}