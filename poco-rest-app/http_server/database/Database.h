#pragma once
#include <Poco/Data/MySQL/Connector.h>
#include <Poco/Data/MySQL/MySQLException.h>
#include <Poco/Data/SessionFactory.h>

#include <string>
#include <functional>

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
    size_t number_of_shards;
    size_t calc_shard_number(std::string target);
    std::string get_sharding_hint(size_t shard_number);
};
} // namespace database