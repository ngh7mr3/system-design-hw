#pragma once
#include <vector>

#include "Database.h"
#include "Poco/JSON/Object.h"

namespace database
{
class Person
{
  private:
    std::string _login;
    std::string _first_name;
    std::string _last_name;
    int _age;

  public:
    Person(){};
    Person(std::string &login, std::string &first_name, std::string &last_name, int &age)
        : _login(login), _first_name(first_name), _last_name(last_name), _age(age)
    {
    }

    const std::string &get_login() const;
    const std::string &get_first_name() const;
    const std::string &get_last_name() const;
    const int &get_age() const;

    std::string &login();
    std::string &first_name();
    std::string &last_name();
    int &age();

    static Person get_by_login(std::string &login);
    static std::vector<Person> read_all();
    static std::vector<Person> search(std::string &first_name, std::string &last_name);
    void save_to_mysql();

    Poco::JSON::Object::Ptr toJSON() const;
};
} // namespace database