/* Authors : Frejoux Gaetan & Niord Mathieu */

#include "parsing_exception.hh"

class invalid_variable : public parsing_exception {

public:

    inline invalid_variable(const std::string& msg) throw() : parsing_exception(msg) {}
    ~invalid_variable() throw() override = default;

};