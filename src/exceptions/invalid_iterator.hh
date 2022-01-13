/* Authors : Frejoux Gaetan & Niord Mathieu */

#include "parsing_exception.hh"

class invalid_iterator : public parsing_exception {

public:

    inline invalid_iterator(const std::string& msg) throw() : parsing_exception(msg) {}
    ~invalid_iterator() throw() override = default;

};