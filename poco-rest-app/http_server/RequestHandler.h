#pragma once

#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/JSON/Object.h>
#include <Poco/URI.h>

enum HTTPMethodCode { GET, POST, UNKNOWN };

class RequestHandler : public Poco::Net::HTTPRequestHandler
{
protected:

  virtual void send(
      Poco::Net::HTTPServerResponse& resp,
      Poco::Net::HTTPResponse::HTTPStatus status,
      Poco::JSON::Object::Ptr data);

  virtual void send(
      Poco::Net::HTTPServerResponse& resp,
      Poco::Net::HTTPResponse::HTTPStatus status,
      const std::string& data = "\n");

  virtual std::string getParam(
      const Poco::URI::QueryParameters& params,
      const std::string& name);

  virtual HTTPMethodCode methodCode(const std::string& val);
};