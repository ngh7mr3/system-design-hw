#include "PersonScheme.h"

#include <exception>
#include <Poco/Data/RecordSet.h>

namespace database
{
Person Person::get_by_login(std::string &login)
{
    try
    {
        Poco::Data::Session session = database::Database::get().create_session();
        Poco::Data::Statement select(session);

        Person a;
        std::string sharding_hint = database::Database::get().get_sharding_hint(database::Database::get().calc_shard_number(login));

        select << "SELECT login, first_name, last_name, age FROM Person where login=?" + sharding_hint,
            Poco::Data::Keywords::into(a._login), Poco::Data::Keywords::into(a._first_name),
            Poco::Data::Keywords::into(a._last_name), Poco::Data::Keywords::into(a._age),
            Poco::Data::Keywords::use(login), Poco::Data::Keywords::range(0, 1);

        std::cout << Poco::format("[get_by_login] -> [%s] -> goes to %s", login, sharding_hint) << std::endl;

        select.execute();
        Poco::Data::RecordSet rs(select);
        if (!rs.moveFirst())
            throw std::logic_error("not found");

        return a;
    }
    catch (const std::exception &e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
        throw;
    }
    catch (...)
    {
        std::cout << "Unknown exception" << std::endl;
        throw;
    }
}

std::vector<Person> Person::read_all()
{
    try
    {
        Poco::Data::Session session = database::Database::get().create_session();
        std::vector<Person> result;

        Person a;

        for (size_t shard_idx = 0; shard_idx < database::Database::get().number_of_shards; ++shard_idx)
        {
            Poco::Data::Statement select(session);
            select << "SELECT login, first_name, last_name, age FROM Person" + database::Database::get().get_sharding_hint(shard_idx),
                Poco::Data::Keywords::into(a._login),
                Poco::Data::Keywords::into(a._first_name), Poco::Data::Keywords::into(a._last_name),
                Poco::Data::Keywords::into(a._age), Poco::Data::Keywords::range(0, 1);

            while (!select.done())
            {
                if (select.execute())
                    result.push_back(a);
            }
        }

        return result;
    }
    catch (const std::exception &e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
        throw;
    }
    catch (...)
    {
        std::cout << "Unknown exception" << std::endl;
        throw;
    }
}

std::vector<Person> Person::search(std::string &first_name, std::string &last_name)
{
    try
    {
        Poco::Data::Session session = database::Database::get().create_session();
        std::vector<Person> result;

        Person a;

        first_name += "%";
        last_name += "%";

        for (size_t shard_idx = 0; shard_idx < database::Database::get().number_of_shards; ++shard_idx)
        {
            Poco::Data::Statement select(session);
            select << "SELECT login, first_name, last_name, age FROM Person where "
                      "first_name LIKE ? and last_name LIKE ?" + database::Database::get().get_sharding_hint(shard_idx),
                Poco::Data::Keywords::into(a._login), Poco::Data::Keywords::into(a._first_name),
                Poco::Data::Keywords::into(a._last_name), Poco::Data::Keywords::into(a._age),
                Poco::Data::Keywords::use(first_name), Poco::Data::Keywords::use(last_name),
                Poco::Data::Keywords::range(0, 1);

            while (!select.done())
            {
                if (select.execute())
                    result.push_back(a);
            }
        }

        return result;
    }
    catch (const std::exception &e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
        throw;
    }
    catch (...)
    {
        std::cout << "Unknown exception" << std::endl;
        throw;
    }
}

void Person::save_to_mysql()
{
    try
    {
        Poco::Data::Session session = database::Database::get().create_session();
        Poco::Data::Statement insert(session);

        std::string sharding_hint = database::Database::get().get_sharding_hint(database::Database::get().calc_shard_number(_login));

        insert << "INSERT INTO Person (login, first_name, last_name, age) VALUES(?, ?, ?, ?)" + sharding_hint,
            Poco::Data::Keywords::use(_login), Poco::Data::Keywords::use(_first_name),
            Poco::Data::Keywords::use(_last_name), Poco::Data::Keywords::use(_age),

            insert.execute();

        std::cout << Poco::format("[save_to_mysql] -> [%s] -> goes to %s", _login, sharding_hint) << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
        throw;
    }
    catch (...)
    {
        std::cout << "Unknown exception" << std::endl;
        throw;
    }
}

Poco::JSON::Object::Ptr Person::toJSON() const
{
    Poco::JSON::Object::Ptr root = new Poco::JSON::Object();

    root->set("login", _login);
    root->set("first_name", _first_name);
    root->set("last_name", _last_name);
    root->set("age", _age);

    return root;
}

const std::string &Person::get_login() const
{
    return _login;
}

std::string &Person::login()
{
    return _login;
}

const std::string &Person::get_first_name() const
{
    return _first_name;
}

std::string &Person::first_name()
{
    return _first_name;
}

const std::string &Person::get_last_name() const
{
    return _last_name;
}

std::string &Person::last_name()
{
    return _last_name;
}

const int &Person::get_age() const
{
    return _age;
}

int &Person::age()
{
    return _age;
}
} // namespace database
