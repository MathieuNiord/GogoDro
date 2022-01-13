#include "double.hh"

Double::Double(double value)
    : value_(value) {}

void Double::visit(Visitor& visitor) const {
    return visitor.visit_double(this);
}