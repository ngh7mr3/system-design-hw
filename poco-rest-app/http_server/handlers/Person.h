#include "../RequestHandler.h"

struct PersonHttpParam {
    static const char* Login;
    static const char* FirstName;
    static const char* LastName;
    static const char* Age;
};

class PersonHandler : public RequestHandler
{
    PersonHandler(){};

    void getPersonByLogin(const std::string& login, Poco::Net::HTTPServerResponse& resp);
    void findPersonByMask(const std::string& first_name, const std::string& last_name, Poco::Net::HTTPServerResponse& resp);
    void addPerson(
        const std::string& login,
        const std::string& first_name,
        const std::string& last_name,
        const std::string& age,
        Poco::Net::HTTPServerResponse& resp
    );

public:
    static Poco::Net::HTTPRequestHandler* create();
    void handleRequest(Poco::Net::HTTPServerRequest& req, Poco::Net::HTTPServerResponse& resp);
};