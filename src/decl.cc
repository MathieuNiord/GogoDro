#include "decl.hh"

Declaration::Declaration(const std::string& var)
    : var_(var) {}

Declaration::~Declaration() {
}

void Declaration::visit(Visitor& visitor) const {
    return visitor.visit_decl(this);
}