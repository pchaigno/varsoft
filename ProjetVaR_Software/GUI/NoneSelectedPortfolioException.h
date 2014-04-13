#ifndef NONESELECTEDPORTFOLIOEXCEPTION_H
#define NONESELECTEDPORTFOLIOEXCEPTION_H

#include <string>
#include <exception>


class NoneSelectedPortfolioException: public std::exception {
public:
    NoneSelectedPortfolioException(std::string msg) {
        this->msg = msg;
    }

    virtual ~NoneSelectedPortfolioException() throw() {

    }

    virtual const char * what() const throw() {
        return this->msg.c_str();
    }

private:
    std::string msg;
};

#endif // NONESELECTEDPORTFOLIOEXCEPTION_H
