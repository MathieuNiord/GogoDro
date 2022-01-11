#include "decl.hh"

Declaration::Declaration(Variable* var)
    : var_(var) {}

Declaration::~Declaration() {
    delete var_;
}

void Declaration::visit(Visitor& visitor) const {
    return visitor.visit_decl(this);
}