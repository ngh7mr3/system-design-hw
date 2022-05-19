#include "AmqpConsumer.h"

using namespace amqp;

void AmqpConsumer::run()
{
    AmqpClient::Channel::ptr_t channel = AmqpConfig::get().createChannel();

    std::string queue = channel->DeclareQueue("tmp");
    std::cout << "declared queue " << queue << std::endl;

    std::string consumer = channel->BasicConsume(queue);
    AmqpClient::Envelope::ptr_t env;

    while(true)
    {
        channel->BasicConsumeMessage(consumer, env, -1);
        std::cout << "[consumer] got message " << env->Message()->Body() << std::endl;
    }

}
