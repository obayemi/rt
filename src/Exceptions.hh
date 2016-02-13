#ifndef _EXCEPTIONS_HH
#define _EXCEPTIONS_HH

/*!
 * \file Exceptions.hh
 * \author obayemi
 */

#include <iostream>
#include <stdexcept>

class NotImplementedException : public std::exception
{
    public:
        virtual char const * what() const throw();
};


class RenderException : public std::exception
{
    public:
        virtual char const * what() const throw();
};

class NotRendered : public RenderException
{
    public:
        virtual char const * what() const throw();
};

class NoIntersect : public RenderException
{
    public:
        virtual char const * what() const throw();
};

#endif // _EXCEPTIONS_HH

