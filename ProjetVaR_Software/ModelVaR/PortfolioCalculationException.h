#pragma once

#include <exception>
#include <QString>
#include "ModelVaR_global.h"

class MODELVARSHARED_EXPORT PortfolioCalculationException: public std::exception
{
public:
    PortfolioCalculationException(std::string msg) {
        this->msg = msg;
    }

    virtual ~PortfolioCalculationException() throw() {

    }

    virtual const char * what() const throw() {
        return this->msg.c_str();
    }

private:
    std::string msg;
};
