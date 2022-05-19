#pragma once
#include <SimpleAmqpClient/SimpleAmqpClient.h>

namespace amqp
{
class AmqpConfig
{
  private:
    AmqpClient::Channel::OpenOpts _opts;
    std::string _default_queue;
    AmqpConfig();

  public:
    static AmqpConfig &get();
    AmqpClient::Channel::ptr_t createChannel();
    std::string getDefaultQueue();
};
} // namespace amqp
