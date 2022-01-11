/* Authors : Frejoux Gaetan & Niord Mathieu */

#ifndef _INTEGER_H
#define _INTEGER_H

#include "expr.hh"

class Integer : public Expression {

	int value_;

public:

	Integer(int value);
	~Integer() = default;

	inline const int get_value() const { return value_; }

	void visit(Visitor& visitor) const;
};

#endif