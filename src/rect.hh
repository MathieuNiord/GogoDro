/* Authors : Frejoux Gaetan & Niord Mathieu */

#ifndef _RECT_H
#define _RECT_H

#include "expr.hh"
#include "inst.hh"

class Rectangle : public Instruction {

	Expression* len_;
	Expression* width_;

public:

	Rectangle(Expression* len, Expression* width);
	~Rectangle();

	inline const Expression* get_len() const { return len_; }
	inline Expression* get_width() const { return width_; }

	void visit(Visitor& visitor) const;
};

#endif