/* Authors : Frejoux Gaetan & Niord Mathieu */

#ifndef PEN_H
#define PEN_H

#include "inst.hh"

class Pen : public Instruction {

	bool state_;

public:

	Pen(bool state);
	~Pen() override = default;

	inline bool get_state() const { return state_; }

	void visit(Visitor& visitor) const;
};

#endif