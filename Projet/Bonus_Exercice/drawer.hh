#ifndef _DRAWER_H
#define _DRAWER_H

#include <iostream>
#include <iterator>
#include <map>

#include "visitor.hh"
#include "seq.hh"
#include "pen.hh"
#include "integer.hh"
#include "var.hh"
#include "ope.hh"
#include "decl.hh"
#include "affect.hh"
#include "move.hh"
#include "rect.hh"
#include "set_color.hh"
#include "for_loop.hh"


class Drawer : public Visitor {

    std::map<std::string, Variable> variables_;
    std::map<std::string, Variable> iterators_;
    unsigned char color_[3] = { 0, 0, 0};

    /**
     * @brief Used to cast the color into a char[3]
     * @param color 
     */
    void get_color(Color color);

    bool check_var(const Variable* var) const;

    void add_iter(const Variable* var);
    void add_var(const Variable* var);
    void erase_iter(const Variable* var);
    void erase_var(const Variable* var);

public:

	void visit_seq(const Sequence* s);
	void visit_pen(const Pen* p);
	void visit_integer(const Integer* i);
	void visit_var(const Variable* v);
	void visit_operation(const Operation* o);
	void visit_decl(const Declaration* d);
	void visit_affect(const Affect* a);
	void visit_move(const MovePen* m);
	void visit_rect(const Rectangle* r);
	void visit_set_color(const SetColor* sc);
	void visit_for(const ForLoop* fl);

};


#endif