#include <iostream>

#include "AmqpConfig.h"
#include "Poco/Runnable.h"
#include "Poco/JSON/Object.h"
#include "Poco/JSON/Parser.h"
#include "Poco/Dynamic/Var.h"

class AmqpConsumer : public Poco::Runnable
{ 
    virtual void run();
};