#include "ope.hh"

Operation::Operation(Expression* left, Operator ope, Expression* right)
    : left_(left), ope_(ope), right_(right) {}

Operation::~Operation() {
    delete left_;
    delete right_;
}

void Operation::visit(Visitor& visitor) const {
    return visitor.visit_operation(this);
}