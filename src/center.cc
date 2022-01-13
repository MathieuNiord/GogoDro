#include "center.hh"

Center::Center() {}

void Center::visit(Visitor& visitor) const {
    return visitor.visit_center(this);
}