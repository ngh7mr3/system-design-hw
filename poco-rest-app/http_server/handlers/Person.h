#include "../RequestHandler.h"

struct PersonHttpParam
{
    static const char *Login;
    static const char *FirstName;
    static const char *LastName;
    static const char *Age;
};

class PersonHandler : public RequestHandler
{
    PersonHandler(){};

    void getPersonByLogin(std::string &login, Poco::Net::HTTPServerResponse &resp);
    void findPersonByMask(std::string &first_name, std::string &last_name, Poco::Net::HTTPServerResponse &resp);
    void addPerson(std::string &login, std::string &first_name, std::string &last_name, std::string &age,
                   Poco::Net::HTTPServerResponse &resp);

  public:
    static Poco::Net::HTTPRequestHandler *create();
    void handleRequest(Poco::Net::HTTPServerRequest &req, Poco::Net::HTTPServerResponse &resp);
};