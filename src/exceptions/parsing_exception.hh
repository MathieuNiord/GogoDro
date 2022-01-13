/* Authors : Frejoux Gaetan & Niord Mathieu */

#ifndef _PARSING_EXCEPTION_H
#define _PARSING_EXCEPTION_H

#include <exception>
#include <string>

class parsing_exception : public std::exception {

    const std::string error_msg_;

public:

    inline parsing_exception(const std::string& msg) throw() : error_msg_(msg) {}
    virtual ~parsing_exception() throw() = default;
    
    inline char const* what() const throw() override {
        return error_msg_.c_str();
    }

};

#endif