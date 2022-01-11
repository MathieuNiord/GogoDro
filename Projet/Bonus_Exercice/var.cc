#include "var.hh"

Variable::Variable(const std::string& name, Expression* value)
    : name_(name), value_(value) {}

Variable::~Variable() {
    delete value_;
}

void Variable::visit(Visitor& visitor) const {
    return visitor.visit_var(this);
}