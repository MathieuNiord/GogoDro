/* Authors : Frejoux Gaetan & Niord Mathieu */

#ifndef _FOR_LOOP_H
#define _FOR_LOOP_H

#include "expr.hh"
#include "inst.hh"

class ForLoop : public Instruction {

	std::string var_;
	Expression* begin_;
	Expression* end_;
	Instruction* body_;

public:

	ForLoop(const std::string& var, Expression* begin, Expression* end, Instruction* body);
	~ForLoop();

	inline const std::string& get_variable() const { return var_; }
	inline const Expression* get_begin() const { return begin_; }
	inline const Expression* get_end() const { return end_; }
	inline const Instruction* get_body() const { return body_; }

	void visit(Visitor& visitor) const;
};

#endif