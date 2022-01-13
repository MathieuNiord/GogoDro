/* Authors : Frejoux Gaetan & Niord Mathieu */

#ifndef _SET_COLOR_H
#define _SET_COLOR_H

#include "inst.hh"
#include "exceptions/unknown_color.hh"

enum Color {
    NOIR,
    BLEU,
    VERT,
    ROUGE,
    ROSE,
    JAUNE,
    VIOLET
};

class SetColor : public Instruction {

    Color color_;

    Color switch_color(const std::string& color) const;

public:

    SetColor(const std::string& color);
    ~SetColor() = default;

    inline const Color get_color() const { return color_; }

    void visit(Visitor& visitor) const;
};

#endif