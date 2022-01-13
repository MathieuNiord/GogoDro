#include "rect.hh"

Rectangle::Rectangle(Expression* len, Expression* width)
    : len_(len), width_(width) {}

Rectangle::~Rectangle() {
    delete len_;
    delete width_;
}

void Rectangle::visit(Visitor& visitor) const {
    return visitor.visit_rect(this);
}