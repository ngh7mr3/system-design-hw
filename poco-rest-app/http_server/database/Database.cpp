#include "Database.h"

#include <Poco/Util/Application.h>

namespace database
{
Database::Database()
{
    // TODO: move out getenv to config?
    _connection_string =
        Poco::format("host=%s;user=%s;db=%s;password=%s", std::string(std::getenv("MYSQL_HOST")),
                     std::string(std::getenv("MYSQL_DATABASE")), std::string(std::getenv("MYSQL_USER")),
                     std::string(std::getenv("MYSQL_PASSWORD")));

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

} // namespace database