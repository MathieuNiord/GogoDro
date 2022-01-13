#include "move_pen.hh"

MovePen::MovePen(const std::string& dir, Expression* len, bool forced)
    : len_(len), forced_drawing_(forced) {
        dir_ = switch_dir(dir);
}

MovePen::~MovePen() {
    delete len_;
}

Direction MovePen::switch_dir(const std::string& dir) const {
    if (dir == "HAUT") return HAUT;
    if (dir == "BAS") return BAS;
    if (dir == "GAUCHE") return GAUCHE;
    if (dir == "DROITE") return DROITE;
    throw unknown_direction("\nLa direction " + dir + " n'est pas reconnue par le langage.\n");
}

void MovePen::visit(Visitor& visitor) const {
    return visitor.visit_move(this);
}