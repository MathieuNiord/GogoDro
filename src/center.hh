/* Authors : Frejoux Gaetan & Niord Mathieu */

#ifndef _CENTER_PEN_H
#define _CENTER_PEN_H

#include "inst.hh"

class Center : public Instruction {

public:

	Center();
	~Center() = default;

	void visit(Visitor& visitor) const;

};

#endif