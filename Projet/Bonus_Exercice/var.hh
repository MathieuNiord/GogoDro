/* Authors : Frejoux Gaetan & Niord Mathieu */

#ifndef _VAR_H
#define _VAR_H

#include "expr.hh"

class Variable : public Expression {

	std::string name_;
	Expression* value_;

public:

	Variable(const std::string& name, Expression* value);
	~Variable();

	inline const std::string& get_name() const { return name_; }
	inline const Expression* get_value() const { return value_; }

	void visit(Visitor& visitor) const;
};

#endif