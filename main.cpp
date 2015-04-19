#include "sqlretriver.h"


int main()
{
    using wltr::Book;

    wltr::Stack<Book> a;

    wltr::fnc::retrieveData(a);

   for(wltr::Stack<Book>::Iterator it = a.begin(); it != a.end(); ++it)
    {
        std::cout << *it;
    }

    return 0;
}

