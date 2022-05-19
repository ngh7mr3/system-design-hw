#include "Poco/ThreadPool.h"
#include "http_server/HttpServer.h"
#include "http_server/amqp/AmqpConsumer.h"

int main(int argc, char *argv[])
{
    /*
    Explanation:
    POCO's server application uses default thread pool as a runner for TCP socket.
    To run worker for writing data from rabbitMQ we append it in parallel via default thread pool.
    */
    AmqpConsumer consumer;
    Poco::ThreadPool::defaultPool().start(consumer);

    http_server::HttpServer server;
    return server.run(argc, argv);
}