/* Authors : Frejoux Gaetan & Niord Mathieu */

#include "parsing_exception.hh"

class unknown_direction : public parsing_exception {

public:

    inline unknown_direction(const std::string& msg) throw() : parsing_exception(msg) {}
    ~unknown_direction() throw() override = default;

};