#include "Person.h"
#include <exception>

#include "../amqp/AmqpConfig.h"
#include "../database/PersonScheme.h"

using namespace amqp;
using namespace Poco;
using namespace Poco::Net;

const char *PersonHttpParam::Login = "login";
const char *PersonHttpParam::FirstName = "first_name";
const char *PersonHttpParam::LastName = "last_name";
const char *PersonHttpParam::Age = "age";

HTTPRequestHandler *PersonHandler::create()
{
    return new PersonHandler();
}

void PersonHandler::getPersonByLogin(std::string &login, Poco::Net::HTTPServerResponse &resp)
{
    try
    {
        database::Person p = database::Person::get_by_login(login);
        send(resp, HTTPResponse::HTTP_OK, p.toJSON());
    }
    catch (std::logic_error &e)
    {
        send(resp, HTTPResponse::HTTP_NOT_FOUND, "Person not found");
    }
}

void PersonHandler::findPersonByMask(std::string &first_name, std::string &last_name,
                                     Poco::Net::HTTPServerResponse &resp)
{
    std::vector<database::Person> results = database::Person::search(first_name, last_name);

    Poco::JSON::Array::Ptr arr = new Poco::JSON::Array();
    for (auto i : results)
        arr->add(i.toJSON());

    send(resp, HTTPResponse::HTTP_OK, arr);
}

void PersonHandler::addPerson(std::string &login, std::string &first_name, std::string &last_name, std::string &age,
                              Poco::Net::HTTPServerResponse &resp)
{
    int _age;
    try
    {
        _age = std::stoi(age);
        if (_age < 0)
            throw std::logic_error("age could not be lower than zero");
    }
    catch (...)
    {
        send(resp, HTTPResponse::HTTP_BAD_REQUEST, "Age parameter is non-valid");
        return;
    }

    database::Person p(login, first_name, last_name, _age);
    try
    {
        AmqpClient::Channel::ptr_t channel = AmqpConfig::get().createChannel();

        std::ostringstream oss;
        Poco::JSON::Stringifier::stringify(p.toJSON(), oss);
        AmqpClient::BasicMessage::ptr_t message = AmqpClient::BasicMessage::Create(oss.str());

        channel->BasicPublish("", AmqpConfig::get().getDefaultQueue(), message);
    }
    catch (std::exception &e)
    {
        send(resp, HTTPResponse::HTTP_BAD_REQUEST, "Person already exists");
        return;
    }

    send(resp, HTTPResponse::HTTP_OK,
         Poco::format("Added new person (%s, %s, %s, %d)", login, first_name, last_name, _age));
}

void PersonHandler::handleRequest(HTTPServerRequest &req, HTTPServerResponse &resp)
{
    URI uri(req.getURI());

    std::string login = getParam(uri.getQueryParameters(), PersonHttpParam::Login);
    std::string first_name = getParam(uri.getQueryParameters(), PersonHttpParam::FirstName);
    std::string last_name = getParam(uri.getQueryParameters(), PersonHttpParam::LastName);
    std::string age = getParam(uri.getQueryParameters(), PersonHttpParam::Age);

    switch (methodCode(req.getMethod()))
    {
    case HTTPMethodCode::GET:
        std::cout << "GET person" << std::endl;
        if (!login.empty() && first_name.empty() && last_name.empty() && age.empty())
        {
            getPersonByLogin(login, resp);
        }
        else if (login.empty() && !first_name.empty() && !last_name.empty() && age.empty())
        {
            findPersonByMask(first_name, last_name, resp);
        }
        else
        {
            send(resp, HTTPResponse::HTTP_BAD_REQUEST, "Bad request");
        }
        break;
    case HTTPMethodCode::POST:
        std::cout << "POST person" << std::endl;
        if (!(login.empty() || first_name.empty() || last_name.empty() || age.empty()))
        {
            addPerson(login, first_name, last_name, age, resp);
        }
        else
        {
            send(resp, HTTPResponse::HTTP_BAD_REQUEST, "Bad request");
        }
        break;
    default:
        std::cout << req.getMethod() << " method not allowed" << std::endl;
        send(resp, HTTPResponse::HTTP_METHOD_NOT_ALLOWED, "Method not allowed");
    }
}