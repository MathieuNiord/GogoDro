/* Authors : Frejoux Gaetan & Niord Mathieu */

#ifndef _DOUBLE_H
#define _DOUBLE_H

#include "expr.hh"

class Double : public Expression {

	double value_;

public:

	Double(double value);
	~Double() = default;

	inline const double get_value() const { return value_; }

	void visit(Visitor& visitor) const;
};

#endif