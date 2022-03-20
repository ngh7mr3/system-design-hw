#include "RequestHandlerFactory.h"
#include "handlers/NotFound.h"

#include <Poco/Util/Application.h>

std::map<std::string, RequestHandlerFactory::HandlerCreator> RequestHandlerFactory::_handlers;

Poco::Net::HTTPRequestHandler* RequestHandlerFactory::getHandler(const std::string& func)
{
    auto found = _handlers.find(func);
    if (found != std::end(_handlers))
        return found->second();

    return new NotFoundHandler();
}

Poco::Net::HTTPRequestHandler* RequestHandlerFactory::createRequestHandler(const Poco::Net::HTTPServerRequest& request)
{
    std::string func = request.getURI().substr(0, request.getURI().find('?'));
    return RequestHandlerFactory::getHandler(func);
}

void RequestHandlerFactory::Register(const std::string& func, const HandlerCreator& creator)
{
    assert(!Poco::Util::Application::instance().initialized());

    _handlers[func] = creator;
}