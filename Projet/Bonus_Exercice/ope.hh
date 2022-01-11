/* Authors : Frejoux Gaetan & Niord Mathieu */

#ifndef _OPE_H
#define _OPE_H

#include "expr.hh"

enum Operator {
    PLUS,
	MINUS,
	MULT,
    DIV
};

class Operation : public Expression {

    Expression* left_;
    Operator ope_;
    Expression* right_;

public:

    Operation(Expression* left, Operator ope, Expression* right);
    ~Operation();

    inline const Expression* get_left() const { return left_; }
    inline const Expression* get_right() const { return right_; }
    inline const Operator get_operator() const { return ope_; }

    void visit(Visitor& visitor) const;

};

#endif