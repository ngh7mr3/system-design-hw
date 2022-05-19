#include <iostream>

#include "AmqpConfig.h"
#include "Poco/Dynamic/Var.h"
#include "Poco/JSON/Object.h"
#include "Poco/JSON/Parser.h"
#include "Poco/Runnable.h"

class AmqpConsumer : public Poco::Runnable
{
    virtual void run();
};