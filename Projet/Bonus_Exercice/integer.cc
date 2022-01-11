#include "integer.hh"

Integer::Integer(int value)
    : value_(value) {}

void Integer::visit(Visitor& visitor) const {
    return visitor.visit_integer(this);
}