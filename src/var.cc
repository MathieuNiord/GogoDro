#include "var.hh"

Variable::Variable(const std::string& name)
    : name_(name) {}

void Variable::visit(Visitor& visitor) const {
    return visitor.visit_var(this);
}