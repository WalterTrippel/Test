#ifndef BOOK_H
#define BOOK_H

#include <iostream>

namespace wltr
{
    class Book;

    namespace fnc
    {
        std::string getGenre(const Book & book);
    }

    class BookException : public std::exception
    {
    private:
        std::string ex;
    public:
        BookException(){ ex = std::string("Book exception occured!");}
        BookException(std::string ex){this->ex = std::string(ex);}

        const char * what() const throw()
        {
            return ex.c_str();
        }
    };

    class Book
    {
    public:
        enum MainGenre
        {
            fiction = 0, nonfiction
        };

        enum FictionGenre
        {
            classic = 0, folklore, legend, fantasy, poetry, horror, mystery
        };

        enum NonfictionGenre
        {
            speech = 0, essay, textbook
        };

        Book();
        Book(std::string name, std::string author, int _maingenre, int _subgenre);
        Book(const Book & other);
        Book(Book && other) = default;

        Book & operator = (const Book & other);
        Book & operator = (Book && other) = default;

        ~Book();

        friend std::ostream & operator << (std::ostream & out, const Book & book);
        friend std::string fnc::getGenre(const Book &book);

    private:
        std::string author;
        std::string name;
        MainGenre maingenre;
        FictionGenre fictiongenre;
        NonfictionGenre nonfictiongenre;
    };
}

#endif // BOOK_H
