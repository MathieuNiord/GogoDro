/* Authors : Frejoux Gaetan & Niord Mathieu */

#ifndef _AFFECT_H
#define _AFFECT_H

#include "expr.hh"
#include "inst.hh"

class Affect : public Instruction {

	std::string var_;
	Expression* value_;

public:

	Affect(const std::string& var, Expression* value);
	~Affect();

	inline const std::string get_var() const { return var_; }
	inline Expression* get_value() const { return value_; }

	void visit(Visitor& visitor) const;
};

#endif