#include "cpp_redis/cpp_redis"
#include <iostream>
#include <string>

#include "Poco/Dynamic/Var.h"
#include "Poco/JSON/Object.h"
#include "Poco/JSON/Parser.h"

namespace cache
{
class Redis
{
  private:
    std::string _host, _port;
    cpp_redis::client _client;
    Redis();

  public:
    static Redis &json_storage();
    Poco::JSON::Object::Ptr get(std::string &key);
    void set(std::string &key, Poco::JSON::Object::Ptr &response);
};
} // namespace cache