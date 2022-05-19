#pragma once
#include <SimpleAmqpClient/SimpleAmqpClient.h>

namespace amqp{
class AmqpConfig
{
    private:
        AmqpClient::Channel::OpenOpts _opts;
        AmqpConfig();

    public:
        static AmqpConfig &get();
        AmqpClient::Channel::ptr_t createChannel();
};
}
