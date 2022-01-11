#include "set_color.hh"

SetColor::SetColor(Color color)
    : color_(color) {}

void SetColor::visit(Visitor& visitor) const {
    return visitor.visit_set_color(this);
}