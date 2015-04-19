#include "book.h"

namespace wltr
{

    Book::Book()
    {

    }

    Book::Book(std::string name, std::string author,
               int _maingenre, int _subgenre):author(author), name(name)
    {
        maingenre = static_cast<MainGenre>(_maingenre);

        switch(maingenre)
        {
            case MainGenre::fiction :
                fictiongenre = FictionGenre(_subgenre); break;

            case MainGenre::nonfiction :
                nonfictiongenre = NonfictionGenre(_subgenre); break;

            default: throw BookException();

        }
    }

    Book::Book(const Book &other):author(other.author), name(other.name),
                                maingenre(other.maingenre), fictiongenre(other.fictiongenre),
                                  nonfictiongenre(other.nonfictiongenre)
    {
    }

    Book & Book::operator = (const Book & other)
    {
        if(this != &other)
        {
            author = other.author;
            name = other.name;
            maingenre = other.maingenre;
            fictiongenre = other.fictiongenre;
            nonfictiongenre = other.nonfictiongenre;
        }
        return * this;
    }

    Book::~Book()
    {

    }

    std::ostream & operator << (std::ostream & out, const Book & book)
    {
        out << "\n\\\\\\\\\\\\\\\\\\\\\\\\---" << book.name << "---/////////////////////\n";
        out << "\tGenre : " << fnc::getGenre(book) << "\n";
        out << "\tAuthor : " << book.author << "\n";

        return out;
    }

    std::string wltr::fnc::getGenre(const Book &book)
    {
        std::string result;

        if(book.maingenre == 0)
        {
            result += "fiction ,";
            switch(book.fictiongenre)
            {
            case Book::FictionGenre::classic :
                result += " classic"; break;
            case Book::FictionGenre::folklore :
                result += " folklore"; break;
            case Book::FictionGenre::legend :
                result += " legend"; break;
            case Book::FictionGenre::fantasy :
                result += " fantasy"; break;
            case Book::FictionGenre::poetry :
                result += " poetry"; break;
            case Book::FictionGenre::horror :
                result += " horror"; break;
            case Book::FictionGenre::mystery :
                result += " mystery"; break;
            }
        }
        else
        {
            result += "nonfiction ,";
            switch(book.nonfictiongenre)
            {
            case Book::NonfictionGenre::speech :
                result += " speech"; break;
            case Book::NonfictionGenre::essay :
                result += " essay"; break;
            case Book::NonfictionGenre::textbook :
                result += " textbook"; break;
            }
        }

        return result;

    }
}

