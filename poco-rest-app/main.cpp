#include "http_server/HttpServer.h"

int main(int argc, char *argv[])
{
    http_server::HttpServer server;
    return server.run(argc, argv);
}