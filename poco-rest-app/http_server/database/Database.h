#pragma once
#include <Poco/Data/MySQL/Connector.h>
#include <Poco/Data/MySQL/MySQLException.h>
#include <Poco/Data/SessionFactory.h>

#include <string>

namespace database
{
class Database
{
  private:
    std::string _connection_string;
    Database();

  public:
    static Database &get();
    Poco::Data::Session create_session();
};
} // namespace database