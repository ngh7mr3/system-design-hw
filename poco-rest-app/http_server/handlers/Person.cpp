#include "Person.h"

#include "../database/Cache.h"
#include "../database/PersonScheme.h"

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
        Poco::JSON::Object::Ptr cached_response = cache::Redis::json_storage().get(login);

        if (cached_response->size() != 0)
        {
            std::cout << "return cached response for getPersonByLogin" << std::endl;
            send(resp, HTTPResponse::HTTP_OK, cached_response);
            return;
        }

        database::Person p = database::Person::get_by_login(login);
        Poco::JSON::Object::Ptr json_resp = p.toJSON();
        send(resp, HTTPResponse::HTTP_OK, json_resp);

        std::cout << "getPersonByLogin: save response to cache" << std::endl;
        cache::Redis::json_storage().set(login, json_resp);
    }
    catch (std::logic_error &e)
    {
        std::cout << "got exception: " << e.what() << std::endl;
        send(resp, HTTPResponse::HTTP_NOT_FOUND, "Person not found");
    }
}

void PersonHandler::findPersonByMask(std::string &first_name, std::string &last_name,
                                     Poco::Net::HTTPServerResponse &resp)
{
    std::string cache_key = Poco::format("mask_%s_%s", first_name, last_name);
    Poco::JSON::Object::Ptr cached_response = cache::Redis::json_storage().get(cache_key);

    if (cached_response->size() != 0)
    {
        std::cout << "return cached response for findPersonByMask" << std::endl;
        send(resp, HTTPResponse::HTTP_OK, cached_response);
        return; 
    }

    std::vector<database::Person> results = database::Person::search(first_name, last_name);

    Poco::JSON::Array::Ptr arr = new Poco::JSON::Array();
    for (auto i : results)
        arr->add(i.toJSON());

    Poco::JSON::Object::Ptr json_resp = new Poco::JSON::Object();
    json_resp->set("result", arr);

    send(resp, HTTPResponse::HTTP_OK, json_resp);

    std::cout << "findPersonByMask: save response to cache" << std::endl;
    cache::Redis::json_storage().set(cache_key, json_resp);
}

void PersonHandler::addPerson(std::string &login, std::string &first_name, std::string &last_name, std::string &age,
                              Poco::Net::HTTPServerResponse &resp)
{
    int _age;
    try
    {
        _age = std::stoi(age);
    }
    catch (...)
    {
        send(resp, HTTPResponse::HTTP_BAD_REQUEST, "Age parameter is non-valid");
        return;
    }

    database::Person p(login, first_name, last_name, _age);
    try
    {
        p.save_to_mysql();
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