#include "pen.hh"

Pen::Pen(bool state)
    : state_(state) {}

void Pen::visit(Visitor& visitor) const {
    return visitor.visit_pen(this);
}