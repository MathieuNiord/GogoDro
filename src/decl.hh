/* Authors : Frejoux Gaetan & Niord Mathieu */

#ifndef _DECL_H
#define _DECL_H

#include "inst.hh"

class Declaration : public Instruction {

	std::string var_;

public:

	Declaration(const std::string& var);
	~Declaration();

	inline const std::string& get_var() const { return var_; }

	void visit(Visitor& visitor) const;
};

#endif