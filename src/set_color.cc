#include "set_color.hh"

SetColor::SetColor(const std::string& color) {
    color_ = switch_color(color);
}

Color SetColor::switch_color(const std::string& color) const {
    if (color == "NOIR") return NOIR;
    if (color == "BLEU") return BLEU;
    if (color == "VERT") return VERT;
    if (color == "ROUGE") return ROUGE;
    if (color == "ROSE") return ROSE;
    if (color == "VIOLET") return VIOLET;
    if (color == "JAUNE") return JAUNE;
    throw unknown_color("\nLa couleur " + color + " n'est pas reconnue par le langage.\n");
}

void SetColor::visit(Visitor& visitor) const {
    return visitor.visit_set_color(this);
}