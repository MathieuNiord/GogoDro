/* Authors : Frejoux Gaetan & Niord Mathieu */

#ifndef _AFFECT_H
#define _AFFECT_H

#include "expr.hh"
#include "inst.hh"
#include "var.hh"

class Affect : public Instruction {

	Variable* var_;
	Expression* value_;

public:

	Affect(Variable* var, Expression* value);
	~Affect();

	inline const Variable* get_var() const { return var_; }
	inline Expression* get_value() const { return value_; }

	void visit(Visitor& visitor) const;
};

#endif