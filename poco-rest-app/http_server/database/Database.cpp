#include "Database.h"

#include <Poco/Util/Application.h>

namespace database
{
Database::Database()
{
    // TODO: move out getenv to config?
    _connection_string =
        Poco::format("host=%s;port=%s;user=%s;db=%s;password=%s", std::string(std::getenv("MYSQL_HOST")),
                     std::string(std::getenv("MYSQL_PORT")), std::string(std::getenv("MYSQL_DATABASE")),
                     std::string(std::getenv("MYSQL_USER")), std::string(std::getenv("MYSQL_PASSWORD")));
    number_of_shards = (size_t)std::stoi(std::string(std::getenv("SHARDS_NUMBER")));
    Poco::Data::MySQL::Connector::registerConnector();
}

Database &Database::get()
{
    static Database _instance;
    return _instance;
}

Poco::Data::Session Database::create_session()
{
    return Poco::Data::Session(
        Poco::Data::SessionFactory::instance().create(Poco::Data::MySQL::Connector::KEY, _connection_string));
}

size_t Database::calc_shard_number(std::string target)
{
    return std::hash<std::string>{}(target) % number_of_shards;
}

std::string Database::get_sharding_hint(size_t shard_number)
{
    return Poco::format("-- sharding:%z", shard_number);
}

} // namespace database