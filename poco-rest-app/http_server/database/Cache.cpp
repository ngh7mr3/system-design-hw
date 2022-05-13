#include "Cache.h"

namespace cache {
Redis::Redis()
{
    _host = std::string(std::getenv("REDIS_HOST"));
    _port = std::string(std::getenv("REDIS_PORT"));

    std::cout << "Redis connecting to " << _host << ":" << _port << std::endl;
    _client.connect(_host, std::stoi(_port), [](const std::string& host, std::size_t port, cpp_redis::connect_state status) {
    if (status == cpp_redis::connect_state::dropped) {
      std::cout << "client disconnected from " << host << ":" << port << std::endl;
    }
  });
}

Redis &Redis::json_storage()
{
    static Redis _instance;
    return _instance;
}

Poco::JSON::Object::Ptr Redis::get(std::string &key)
{
    std::cout << "CACHE GET, key " << key << std::endl;
    Poco::JSON::Object::Ptr object = new Poco::JSON::Object();

    _client.get(key, [&](cpp_redis::reply& reply) {
        if (reply.is_string()) {
            std::string response = reply.as_string();
            if (response.empty())
                return;
            Poco::JSON::Parser parser;
            Poco::Dynamic::Var result = parser.parse(response);
            object = result.extract<Poco::JSON::Object::Ptr>();
        }
    });
    _client.sync_commit();

    return object;
}

void Redis::set(std::string &key, Poco::JSON::Object::Ptr &response)
{
    std::cout << "CACHE SET, key " << key << std::endl;

    std::ostringstream oss;
    Poco::JSON::Stringifier::stringify(response, oss);

    _client.set(key, oss.str());
}

}