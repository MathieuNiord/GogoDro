/* Authors : Frejoux Gaetan & Niord Mathieu */

#ifndef _CIRCLE_H
#define _CIRCLE_H

#include "expr.hh"
#include "inst.hh"

class Circle : public Instruction {

	Expression* diam_;

public:

	Circle(Expression* diam);
	~Circle();

	inline const Expression* get_diam() const { return diam_; }

	void visit(Visitor& visitor) const;
};

#endif