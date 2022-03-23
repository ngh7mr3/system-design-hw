#pragma once

#include <Poco/Util/Application.h>
#include <Poco/Util/OptionSet.h>
#include <Poco/Util/ServerApplication.h>

#include <memory>
#include <string>
#include <vector>

#include "RequestHandlerFactory.h"

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

} // namespace http_server