#include "AmqpConsumer.h"
#include "../database/PersonScheme.h"

using namespace amqp;

void AmqpConsumer::run()
{
    AmqpClient::Channel::ptr_t channel = AmqpConfig::get().createChannel();

    std::string queue = channel->DeclareQueue(AmqpConfig::get().getDefaultQueue());
    std::cout << "declared queue " << queue << std::endl;

    std::string consumer = channel->BasicConsume(queue);
    AmqpClient::Envelope::ptr_t env;

    while(true)
    {
        channel->BasicConsumeMessage(consumer, env, -1);
        std::string message_body = env->Message()->Body();
        std::cout << "[consumer][msg] " << message_body << std::endl;

        try {
            Poco::JSON::Parser parser;
            Poco::Dynamic::Var result = parser.parse(message_body);
            Poco::JSON::Object::Ptr person_json = result.extract<Poco::JSON::Object::Ptr>();

            database::Person person(person_json);
            std::cout << "[consumer] save new person message: " << person.login() << std::endl;
            person.save_to_mysql();
        }
        catch (...)
        {
            std::cout << "[consumer] cannot save new person" << std::endl;
        }
    }

}
