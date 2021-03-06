#include "affect.hh"

Affect::Affect(const std::string& var, Expression* value)
    : var_(var), value_(value) {}

Affect::~Affect() {
    delete value_;
}

void Affect::visit(Visitor& visitor) const {
    return visitor.visit_affect(this);
}