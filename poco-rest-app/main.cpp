#include "Poco/ThreadPool.h"
#include "Poco/Runnable.h"
#include "http_server/HttpServer.h"

class WorkerRunnable : public Poco::Runnable
{
    void run_calc()
    {
        for (int i=0; i<10; ++i)
            std::cout << "worker::" << i << std::endl;
    }

    virtual void run()
    {
        std::cout << "Worker starting" << std::endl;
        run_calc();
    }
};

int main(int argc, char *argv[])
{
    /*
    Explanation:
    POCO's server application uses default thread pool as a runner for TCP socket.
    To run worker for writing data from rabbitMQ we append it in parallel via default thread pool.
    */
    WorkerRunnable worker;
    Poco::ThreadPool::defaultPool().start(worker);

    http_server::HttpServer server;
    return server.run(argc, argv);
}