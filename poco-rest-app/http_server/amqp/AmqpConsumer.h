#include <iostream>

#include "AmqpConfig.h"
#include "Poco/Runnable.h"

class AmqpConsumer : public Poco::Runnable
{
    virtual void run();
};