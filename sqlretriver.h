#ifndef SQLRETRIVER
#define SQLRETRIVER

#include "stack.h"
#include "book.h"

#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

namespace wltr
{
    namespace fnc
    {
        template<typename T>
        void retrieveData(wltr::Stack<T> & catalogue)
        {
            sql::Driver *driver;
            sql::Connection *con;
            sql::Statement *stmt;
            sql::ResultSet *res;

            driver = get_driver_instance();
            con = driver->connect("localhost", "walter", "1123581321");
            con->setSchema("Books");

            stmt = con->createStatement();
            res = stmt->executeQuery("SELECT * FROM Data");

           Book * current_book;

            while (res->next())
            {
                std::string name = std::string(res->getString(2).asStdString());
                std::string author = std::string(res->getString(3).asStdString());

                int _main = std::stoi(static_cast<std::string>(res->getString(4)));
                int _sub = std::stoi(static_cast<std::string>(res->getString(5)));

                current_book = new Book(name, author, _main, _sub);

                catalogue.push(*current_book);

                current_book = nullptr;
            }
            delete res;
            delete stmt;
            delete con;

        }
    }
}

#endif // SQLRETRIVER

