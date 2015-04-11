#include "stack.h"
#include "book.h"



int main()
{

    wltr::Stack<int> a{1, 3, 7};

    for(wltr::Stack<int>::Iterator it = a.begin(); it != a.end(); ++it)
    {
        std::cout << *it;
    }

    a.pop();
    a.pop();
    a.pop();
    std::cout << "\t" << a[0];

    return 0;
}

