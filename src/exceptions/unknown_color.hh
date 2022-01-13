/* Authors : Frejoux Gaetan & Niord Mathieu */

#include "parsing_exception.hh"

class unknown_color : public parsing_exception {

public:

    inline unknown_color(const std::string& msg) throw() : parsing_exception(msg) {}
    ~unknown_color() throw() override = default;

};