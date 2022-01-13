/* Auteurs : Frejoux Gaetan & Niord Mathieu */

#ifndef _PROG_H
#define _PROG_H

#include "inst.hh"

class Prog : public Instruction {

	Instruction* prog_;

 public:

	Prog(Instruction* prog);
	~Prog();
	
	inline const Instruction* get_prog() const { return prog_; }

	void visit(Visitor& visitor) const;
};

#endif