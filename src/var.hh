/* Authors : Frejoux Gaetan & Niord Mathieu */

#ifndef _VAR_H
#define _VAR_H

#include "expr.hh"

class Variable : public Expression {

	std::string name_;

public:

	Variable(const std::string& name);
	~Variable() = default;

	inline const std::string& get_name() const { return name_; }

	void visit(Visitor& visitor) const;
};

#endif