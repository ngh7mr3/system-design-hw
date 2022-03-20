#pragma once

#include <memory>
#include <string>
#include <vector>
#include "RequestHandlerFactory.h"

#include <Poco/Util/ServerApplication.h>
#include <Poco/Util/Application.h>
#include <Poco/Util/OptionSet.h>

namespace http_server
{

class HttpServer : public Poco::Util::ServerApplication
{
public:
    HttpServer();
    ~HttpServer();

protected:
    void initialize(Poco::Util::Application &self);
    void uninitialize();
    void defineOptions(Poco::Util::OptionSet &options);
    int main(const std::vector<std::string> &args);
};

}