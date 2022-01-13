/* Authors : Frejoux Gaetan & Niord Mathieu */

#ifndef _MOVE_PEN_H
#define _MOVE_PEN_H

#include "inst.hh"
#include "expr.hh"
#include "exceptions/unknown_direction.hh"

enum Direction {
	HAUT,
	BAS,
	GAUCHE,
	DROITE
};

class MovePen : public Instruction {

	Direction dir_;
	Expression* len_;
	bool forced_drawing_;

	Direction switch_dir(const std::string& dir) const;

public:

	MovePen(const std::string& dir, Expression* len, bool forced = false);
	~MovePen();

	inline const Direction get_dir() const { return dir_; }
	inline const Expression* get_len() const { return len_; }
	inline const bool is_forced() const { return forced_drawing_; }

	void visit(Visitor& visitor) const;

};

#endif