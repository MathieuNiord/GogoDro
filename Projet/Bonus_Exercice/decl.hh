/* Authors : Frejoux Gaetan & Niord Mathieu */

#ifndef _DECL_H
#define _DECL_H

#include "expr.hh"
#include "inst.hh"
#include "var.hh"

class Declaration : public Instruction {

	Variable* var_;

public:

	Declaration(Variable* var);
	~Declaration();

	inline const Variable* get_var() const { return var_; }

	void visit(Visitor& visitor) const;
};

#endif