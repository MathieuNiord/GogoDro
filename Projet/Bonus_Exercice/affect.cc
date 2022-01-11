#include "affect.hh"

Affect::Affect(Variable* var, Expression* value)
    : var_(var), value_(value) {}

Affect::~Affect() {
    delete var_;
    delete value_;
}

void Affect::visit(Visitor& visitor) const {
    return visitor.visit_affect(this);
}