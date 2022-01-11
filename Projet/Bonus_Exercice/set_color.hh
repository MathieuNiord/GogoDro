/* Authors : Frejoux Gaetan & Niord Mathieu */

#ifndef _SET_COLOR_H
#define _SET_COLOR_H

#include "inst.hh"

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

public:

    SetColor(Color color);
    ~SetColor() = default;

    inline Color const get_color() const { return color_; }

    void visit(Visitor& visitor) const;
};

#endif