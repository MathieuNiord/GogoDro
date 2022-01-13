#include "circle.hh"

Circle::Circle(Expression* diam)
    : diam_(diam) {}

Circle::~Circle() {
    delete diam_;
}

void Circle::visit(Visitor& visitor) const {
    return visitor.visit_circle(this);
}