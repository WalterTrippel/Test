#include "stack.h"
#include "book.h"



int main()
{

    wltr::Stack<int> a{1, 3, 7};

    for(wltr::Stack<int>::Iterator it = a.begin(); it != a.end(); ++it)
    {
        std::cout << "\t" << *it;
    }

    return 0;
}

