#include "move.hh"

MovePen::MovePen(Direction dir, Expression* expr)
    : dir_(dir), len_(expr) {}

MovePen::~MovePen() {
    delete len_;
}

void MovePen::visit(Visitor& visitor) const {
    return visitor.visit_move(this);
}