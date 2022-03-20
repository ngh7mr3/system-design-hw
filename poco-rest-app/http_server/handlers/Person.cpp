#include "Person.h"

using namespace Poco;
using namespace Poco::Net;

const char* PersonHttpParam::Login = "login";
const char* PersonHttpParam::FirstName = "first_name";
const char* PersonHttpParam::LastName = "last_name";
const char* PersonHttpParam::Age = "age";

HTTPRequestHandler* PersonHandler::create()
{
    return new PersonHandler();
}

void PersonHandler::getPersonByLogin(const std::string& login, Poco::Net::HTTPServerResponse& resp)
{
    if (login == "admin")
    {
        Poco::JSON::Object::Ptr ret = new Poco::JSON::Object();

        ret->set(PersonHttpParam::Login, "admin");
        ret->set(PersonHttpParam::FirstName, "Foo");
        ret->set(PersonHttpParam::LastName, "Bar");
        ret->set(PersonHttpParam::Age, "23");

        send(resp, HTTPResponse::HTTP_OK, ret);
    }
    else {
        send(resp, HTTPResponse::HTTP_NOT_FOUND, "Not found");
    }

}

void PersonHandler::findPersonByMask(const std::string& first_name, const std::string& last_name, Poco::Net::HTTPServerResponse& resp)
{
    Poco::JSON::Object::Ptr ret = new Poco::JSON::Object();
    ret->set(PersonHttpParam::FirstName, first_name);
    ret->set(PersonHttpParam::LastName, last_name);

    send(resp, HTTPResponse::HTTP_OK, ret);
}

void PersonHandler::addPerson(
    const std::string& login,
    const std::string& first_name,
    const std::string& last_name,
    const std::string& age,
    Poco::Net::HTTPServerResponse& resp
)
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

    send(resp, HTTPResponse::HTTP_OK, Poco::format("Added new user %s %s %s %d", login, first_name, last_name, _age));
}

void PersonHandler::handleRequest(HTTPServerRequest& req, HTTPServerResponse& resp)
{
    URI uri(req.getURI());

    std::string login = getParam(uri.getQueryParameters(), PersonHttpParam::Login);
    std::string first_name = getParam(uri.getQueryParameters(), PersonHttpParam::FirstName);
    std::string last_name = getParam(uri.getQueryParameters(), PersonHttpParam::LastName);
    std::string age = getParam(uri.getQueryParameters(), PersonHttpParam::Age);

    switch (methodCode(req.getMethod())) {
        case HTTPMethodCode::GET:
            std::cout << "GET person" << std::endl;
            if (!login.empty() && first_name.empty() && last_name.empty() && age.empty()) { getPersonByLogin(login, resp); }
            else if (login.empty() && !first_name.empty() && !last_name.empty() && age.empty()) { findPersonByMask(first_name, last_name, resp); }
            else { send(resp, HTTPResponse::HTTP_BAD_REQUEST, "Bad request"); }
            break;
        case HTTPMethodCode::POST:
            std::cout << "POST person" << std::endl;
            if (!(login.empty() || first_name.empty() || last_name.empty() || age.empty())) { addPerson(login, first_name, last_name, age, resp); }
            else { send(resp, HTTPResponse::HTTP_BAD_REQUEST, "Bad request"); }
            break;
        default:
            std::cout << req.getMethod() << " method not allowed" << std::endl;
            send(resp, HTTPResponse::HTTP_METHOD_NOT_ALLOWED, "Method not allowed");
    }
}