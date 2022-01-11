/* Authors : Frejoux Gaetan & Niord Mathieu */

#ifndef _MOVE_H
#define _MOVE_H

#include "inst.hh"
#include "expr.hh"

enum Direction {
	HAUT,
	BAS,
	GAUCHE,
	DROITE
};

class MovePen : public Instruction {

	Direction dir_;
	Expression* len_;

public:

	MovePen(Direction dir, Expression* expr);
	~MovePen();

	inline const Direction get_dir() const { return dir_; }
	inline const Expression* get_len() const { return len_; }

	void visit(Visitor& visitor) const;
};


#endif