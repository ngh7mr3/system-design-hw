#include "AmqpConfig.h"
#include <iostream>

using namespace amqp;

AmqpConfig::AmqpConfig()
{
    _opts.host = getenv("RABBITMQ_HOST");
    _opts.port = std::stoi(getenv("RABBITMQ_PORT"));
    _opts.auth = AmqpClient::Channel::OpenOpts::BasicAuth(getenv("RABBITMQ_USER"), getenv("RABBITMQ_PASSWORD"));

    _default_queue = getenv("RABBITMQ_EXCHANGE_QUEUE");
}

AmqpConfig &AmqpConfig::get()
{
    static AmqpConfig _instance;
    return _instance;
}

AmqpClient::Channel::ptr_t AmqpConfig::createChannel()
{
    try
    {
        return AmqpClient::Channel::Open(_opts);
    }
    catch (...)
    {
        std::cout << "could not connect to broker, it is not ready, exiting..." << std::endl;
        std::exit(127);
    }
}

std::string AmqpConfig::getDefaultQueue()
{
    return _default_queue;
}